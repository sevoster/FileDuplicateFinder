#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include <QDir>
#include "iduplicatefinder.h"
#include "ifilecomparator.h"

class DuplicateFinder : public IDuplicateFinder
{
public:
    DuplicateFinder(std::unique_ptr<IFileComparator> fileComparator);

    // IDuplicateFinder interface
    virtual QList<QStringList> getDuplicates(const QDir& dirPath, bool recursive) override;

private:
    std::unique_ptr<IFileComparator> m_fileComparator;
};

#endif // DUPLICATEFINDER_H
