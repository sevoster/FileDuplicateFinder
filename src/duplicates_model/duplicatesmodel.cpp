#include "duplicatesmodel.h"
#include "duplicatefinder.h"
#include "hashfilecomparator.h"
#include "bytefilecomparator.h"

DuplicatesModel::DuplicatesModel(QObject *parent) : QAbstractListModel (parent)
{

}

void DuplicatesModel::findDuplicates(const QUrl &directoryUrl, bool recursive)
{
    QDir dir(directoryUrl.toLocalFile());
    if (!dir.exists())
    {

    }
    beginResetModel();
    ByteFileComparator fileComparator;
    DuplicateFinder finder(dir, recursive, &fileComparator);
    m_duplicates = finder.getDuplicates();
    endResetModel();
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
