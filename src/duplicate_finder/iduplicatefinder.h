#ifndef IDUPLICATEFINDER_H
#define IDUPLICATEFINDER_H

#include <QList>
#include <QString>

class IDuplicateFinder
{
public:
    virtual ~IDuplicateFinder() = default;
    virtual QList<QStringList> getDuplicates() = 0;
    virtual QStringList getFiles() = 0;
};

#endif // IDUPLICATEFINDER_H
