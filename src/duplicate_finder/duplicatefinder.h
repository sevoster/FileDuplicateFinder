#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include "iduplicatefinder.h"

class DuplicateFinder : public IDuplicateFinder
{
public:
    DuplicateFinder(const QString& dirPath, bool recursive);

    // IDuplicateFinder interface
    virtual QStringList getDuplicates() override;
    virtual QStringList getFiles() override;

private:
    QString m_dirPath;
    bool m_isRecursive;
};

#endif // DUPLICATEFINDER_H
