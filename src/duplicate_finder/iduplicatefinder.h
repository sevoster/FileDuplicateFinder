#ifndef IDUPLICATEFINDER_H
#define IDUPLICATEFINDER_H

#include <QList>
#include <QString>
#include <QDir>

class IDuplicateFinder
{
public:
    virtual ~IDuplicateFinder() = default;
    virtual QList<QStringList> getDuplicates(const QDir& dir, bool recursive) = 0;
};

#endif // IDUPLICATEFINDER_H
