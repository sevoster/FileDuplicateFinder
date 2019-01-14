#ifndef IDUPLICATEFINDER_H
#define IDUPLICATEFINDER_H

#include <QList>
#include <QPair>
#include <QString>
#include <QDir>

class IDuplicateFinder
{
public:
    virtual ~IDuplicateFinder() = default;
    virtual QList<QPair<QString, QStringList>> getDuplicates(const QDir& dirLeft, const QDir& dirRight, bool recursive) = 0;
};

#endif // IDUPLICATEFINDER_H
