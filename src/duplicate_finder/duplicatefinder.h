#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include <QDir>
#include "iduplicatefinder.h"
#include "ifilecomparator.h"

class DuplicateFinder : public IDuplicateFinder
{
public:
    DuplicateFinder(const QDir& dirPath, bool recursive, IFileComparator *fileComparator);

    // IDuplicateFinder interface
    virtual QList<QStringList> getDuplicates() override;
    virtual QStringList getFiles() override;

private:
    QDir m_dirPath;
    bool m_isRecursive;
    IFileComparator *m_fileComparator;
};

#endif // DUPLICATEFINDER_H
