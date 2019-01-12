#ifndef DUPLICATEDATAMODEL_H
#define DUPLICATEDATAMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QUrl>

#include "iduplicatefinder.h"
#include "ifilecomparator.h"

enum DuplicateDataRoles
{
    DuplicateGroup = Qt::UserRole + 1
};

class DuplicatesModel : public QAbstractListModel
{
    static QMap<QString, std::function<IFileComparator*()>> comparerAlgos;

    Q_PROPERTY(QStringList algos READ getCompareAlgos CONSTANT)

    Q_OBJECT
public:
    DuplicatesModel(QObject *parent = nullptr);

    Q_INVOKABLE void findDuplicates(const QUrl& dir, bool recursive);
    Q_INVOKABLE void initFinder(const QString& algoName);

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QStringList getCompareAlgos() const;

signals:
    void submittedMessage(const QString& message);

private:
    enum class MessageType
    {
        Error,
        Warning,
        Info
    };

    void submitMessage(const QString& message, MessageType type = MessageType::Info);

    std::unique_ptr<IDuplicateFinder> m_duplicateFinder;
    QList<QStringList> m_duplicates;

};

#endif // DUPLICATEDATAMODEL_H
