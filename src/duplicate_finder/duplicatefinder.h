#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include "iduplicatefinder.h"

class DuplicateFinder : public IDuplicateFinder
{
public:
    DuplicateFinder(const QString& dirPath, bool recursive);

    // IDuplicateFinder interface
    virtual QList<QString> getDuplicates() override;
    virtual QList<QString> getFiles() override;
};

#endif // DUPLICATEFINDER_H
