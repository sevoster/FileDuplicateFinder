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
    static QMap<QString, std::function<IDuplicateFinder*(std::unique_ptr<IFileComparator>)>> finderTypes;

    Q_PROPERTY(QStringList comparatorNames READ getCompareAlgos CONSTANT)
    Q_PROPERTY(QStringList finderTypes READ getFinderTypes CONSTANT)
    Q_PROPERTY(bool isRelative MEMBER m_isRelative NOTIFY isRelativeChanged)

    Q_OBJECT
public:
    DuplicatesModel(QObject *parent = nullptr);

    Q_INVOKABLE void findDuplicates(const QString &directoryPath, bool recursive);
    Q_INVOKABLE void initFinder(const QString &finderType, const QString& algoName);

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    QStringList getCompareAlgos() const;
    QStringList getFinderTypes() const;

signals:
    void submittedMessage(const QString& message);
    void isRelativeChanged();

public slots:
    void onIsRelativeChanged();

private:
    enum class MessageType
    {
        Error,
        Warning,
        Info
    };

    void submitMessage(const QString& message, MessageType type = MessageType::Info);
    void updatePaths();

    std::unique_ptr<IDuplicateFinder> m_duplicateFinder;
    QList<QStringList> m_duplicateGroups;
    bool m_isRelative;
    QDir m_workDir;

};

#endif // DUPLICATEDATAMODEL_H
