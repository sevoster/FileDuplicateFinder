#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include <memory>
#include <QDir>
#include "iduplicatefinder.h"
#include "ifilecomparator.h"

class DuplicateFinder : public IDuplicateFinder
{
public:
    DuplicateFinder(std::unique_ptr<IFileComparator> fileComparator);

    // IDuplicateFinder interface
    virtual QList<QStringList> getDuplicates(const QDir& dirLeft, const QDir& dirRight, bool recursive) override;

protected:
    std::unique_ptr<IFileComparator> m_fileComparator;
};

#endif // DUPLICATEFINDER_H
