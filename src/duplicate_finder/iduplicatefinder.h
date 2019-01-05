#ifndef IDUPLICATEFINDER_H
#define IDUPLICATEFINDER_H

#include <QList>
#include <QString>

class IDuplicateFinder
{
public:
    virtual ~IDuplicateFinder() = default;
    virtual QList<QString> getDuplicates() = 0;
    virtual QList<QString> getFiles() = 0;
};

#endif // IDUPLICATEFINDER_H
