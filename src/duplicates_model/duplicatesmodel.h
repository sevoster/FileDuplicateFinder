#ifndef DUPLICATEDATAMODEL_H
#define DUPLICATEDATAMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QUrl>

enum DuplicateDataRoles
{
    DuplicateGroup = Qt::UserRole + 1
};

class DuplicatesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DuplicatesModel(QObject *parent = nullptr);

    Q_INVOKABLE void findDuplicates(const QUrl& dir, bool recursive);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QList<QStringList> m_duplicates;

};

#endif // DUPLICATEDATAMODEL_H
