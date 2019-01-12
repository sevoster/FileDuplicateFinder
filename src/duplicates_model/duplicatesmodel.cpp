#include "duplicatesmodel.h"
#include "duplicatefinder.h"
#include "hashfilecomparator.h"
#include "bytefilecomparator.h"

QMap<QString, std::function<IFileComparator*()>> DuplicatesModel::comparerAlgos = {
{"Hash", [] { return new HashFileComparator; }},
{"Byte", [] { return new ByteFileComparator; }}
};

DuplicatesModel::DuplicatesModel(QObject *parent) : QAbstractListModel (parent), m_duplicateFinder(nullptr)
{
    m_duplicateFinder.reset(new DuplicateFinder(std::unique_ptr<HashFileComparator>(new HashFileComparator)));
}

void DuplicatesModel::findDuplicates(const QUrl &directoryUrl, bool recursive)
{
    if (m_duplicateFinder == nullptr)
    {
        submitMessage("Duplicate Finder is not inited", MessageType::Error);
        return;
    }

    QDir dir(directoryUrl.toLocalFile());
    if (!dir.exists())
    {
        submitMessage("Directory does not exist", MessageType::Error);
        return;
    }

    beginResetModel();
    m_duplicates.clear();

    bool exception = false;

    try {
        m_duplicates = m_duplicateFinder->getDuplicates(dir, recursive);
    } catch (const std::runtime_error& e) {
        submitMessage(e.what(), MessageType::Error);
        exception = true;
    }

    endResetModel();

    if (exception)
        return;

    if (m_duplicates.empty())
    {
        submitMessage("No duplicates found");
    }
    else
    {
        submitMessage(QString("Found %1 duplicate groups").arg(m_duplicates.size()));
    }
}

void DuplicatesModel::initFinder(const QString &algoName)
{
    if (!comparerAlgos.contains(algoName))
    {
        submitMessage("Unsupported comparer algorithm");
        return;
    }

    std::unique_ptr<IFileComparator> comparator(comparerAlgos[algoName]());
    m_duplicateFinder.reset(new DuplicateFinder(std::move(comparator)));
}

int DuplicatesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return m_duplicates.size();
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
        return m_duplicates[row];
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
