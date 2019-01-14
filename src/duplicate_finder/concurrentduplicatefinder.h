#ifndef CONCURRENTDUPLICATEFINDER_H
#define CONCURRENTDUPLICATEFINDER_H

#include "duplicatefinder.h"

class ConcurrentDuplicateFinder : public DuplicateFinder
{
public:
    ConcurrentDuplicateFinder(std::unique_ptr<IFileComparator> fileComparator);

    // IDuplicateFinder interface
    virtual QList<QPair<QString, QStringList>> getDuplicates(const QDir &dirLeft, const QDir& dirRight, bool recursive) override;
};

#endif // CONCURRENTDUPLICATEFINDER_H
