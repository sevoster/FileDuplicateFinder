#include "duplicatesmodel.h"
#include "duplicatefinder.h"
#include "concurrentduplicatefinder.h"
#include "hashfilecomparator.h"
#include "bytefilecomparator.h"


QMap<QString, std::function<IFileComparator*()>> DuplicatesModel::comparerAlgos = {
{"Hash", [] { return new HashFileComparator; }},
{"Byte", [] { return new ByteFileComparator; }}
};

QMap<QString, std::function<IDuplicateFinder*(std::unique_ptr<IFileComparator>)>> DuplicatesModel::finderTypes = {
{"Sequential", [] (std::unique_ptr<IFileComparator> comparator) { return new DuplicateFinder(std::move(comparator)); }},
{"Concurrent", [] (std::unique_ptr<IFileComparator> comparator) { return new ConcurrentDuplicateFinder(std::move(comparator)); }}
};

DuplicatesModel::DuplicatesModel(QObject *parent) : QAbstractListModel (parent), m_duplicateFinder(nullptr), m_isRelative(false)
{
    connect(this, SIGNAL(isRelativeChanged()), this, SLOT(onIsRelativeChanged()));
}

void DuplicatesModel::findDuplicates(const QString &leftDirPath, const QString &rightDirPath, bool recursive)
{
    beginResetModel();
    m_duplicateGroups.clear();

    if (m_duplicateFinder == nullptr)
    {
        submitMessage("Duplicate Finder is not inited", MessageType::Error);
        endResetModel();
        return;
    }

    QUrl leftUrl = QUrl::fromUserInput(leftDirPath);
    QUrl rightUrl = QUrl::fromUserInput(rightDirPath);

    if (!leftUrl.isValid() || leftUrl.isEmpty() || !leftUrl.isLocalFile() || !rightUrl.isValid() || rightUrl.isEmpty() || !rightUrl.isLocalFile())
    {
        submitMessage("Path is not valid", MessageType::Error);
        endResetModel();
        return;
    }

    QDir leftDir(leftUrl.toLocalFile());
    QDir rightDir(rightUrl.toLocalFile());

    if (!leftDir.exists() || !rightDir.exists())
    {
        submitMessage("Directory does not exist", MessageType::Error);
        endResetModel();
        return;
    }

    bool exception = false;

    try {
        m_duplicateGroups = m_duplicateFinder->getDuplicates(leftDir, rightDir, recursive);
    } catch (const std::runtime_error& e) {
        submitMessage(e.what(), MessageType::Error);
        exception = true;
    }

    if (m_isRelative)
        updatePaths();

    endResetModel();

    if (exception)
        return;

    if (m_duplicateGroups.empty())
    {
        submitMessage("No duplicates found");
    }
    else
    {
        submitMessage(QString("Found %1 duplicate groups").arg(m_duplicateGroups.size()));
    }
}

void DuplicatesModel::initFinder(const QString& finderType, const QString &algoName)
{
    if (!finderTypes.contains(finderType))
    {
        submitMessage("Unsupported finder type", MessageType::Error);
        return;
    }

    if (!comparerAlgos.contains(algoName))
    {
        submitMessage("Unsupported comparer algorithm", MessageType::Error);
        return;
    }

    std::unique_ptr<IFileComparator> comparator(comparerAlgos[algoName]());
    m_duplicateFinder.reset(finderTypes[finderType](std::move(comparator)));
}

int DuplicatesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return m_duplicateGroups.size();
}

QVariant DuplicatesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    int row = index.row();
    switch (role) {
    case DuplicateDataRoles::DuplicateGroup:
        return m_duplicateGroups[row];
    }

    return QVariant();
}

QHash<int, QByteArray> DuplicatesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[DuplicateDataRoles::DuplicateGroup] = "duplicateGroup";
    return roles;
}

QStringList DuplicatesModel::getCompareAlgos() const
{
    return comparerAlgos.keys();
}

QStringList DuplicatesModel::getFinderTypes() const
{
    return finderTypes.keys();
}

void DuplicatesModel::onIsRelativeChanged()
{
    beginResetModel();

    updatePaths();

    endResetModel();
}

void DuplicatesModel::submitMessage(const QString &message, MessageType type)
{
    QString prefix;
    switch (type)
    {
    case MessageType::Info:
        prefix = "INFO";
        break;
    case MessageType::Error:
        prefix = "ERROR";
        break;
    case MessageType::Warning:
        prefix = "WARNING";
        break;
    }
    emit submittedMessage(prefix + ": " + message);
}

void DuplicatesModel::updatePaths()
{
//    for (auto& group : m_duplicateGroups)
//    {
//        for (auto& filePath : group)
//        {
//            filePath = m_isRelative ? m_workDir.relativeFilePath(filePath) : m_workDir.absoluteFilePath(filePath);
//        }
//    }
}
