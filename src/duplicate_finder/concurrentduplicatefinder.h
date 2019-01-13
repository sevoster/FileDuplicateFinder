#ifndef CONCURRENTDUPLICATEFINDER_H
#define CONCURRENTDUPLICATEFINDER_H

#include "duplicatefinder.h"

class ConcurrentDuplicateFinder : public DuplicateFinder
{
public:
    ConcurrentDuplicateFinder(std::unique_ptr<IFileComparator> fileComparator);

    // IDuplicateFinder interface
    virtual QList<QStringList> getDuplicates(const QDir &dir, bool recursive) override;
};

#endif // CONCURRENTDUPLICATEFINDER_H
