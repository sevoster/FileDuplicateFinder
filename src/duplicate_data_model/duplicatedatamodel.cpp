#include "duplicatedatamodel.h"
#include "duplicatefinder.h"
#include "hashfilecomparator.h"

DuplicateDataModel::DuplicateDataModel(QObject *parent) : QAbstractListModel (parent)
{

}

void DuplicateDataModel::findDuplicates(const QUrl &directoryUrl, bool recursive)
{
    beginResetModel();
    QDir dir(directoryUrl.toLocalFile());
    DuplicateFinder finder(dir, recursive, new HashFileComparator());
    m_duplicates = finder.getDuplicates();
    endResetModel();
}

int DuplicateDataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return m_duplicates.size();
}

QVariant DuplicateDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    int row = index.row();
    switch (role) {
    case DuplicateDataRoles::DuplicateGroup:
        return m_duplicates[row].join("\n");
    }

    return QVariant();
}

QHash<int, QByteArray> DuplicateDataModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[DuplicateDataRoles::DuplicateGroup] = "duplicateGroup";
    return roles;
}
