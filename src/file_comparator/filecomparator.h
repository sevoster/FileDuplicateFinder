#ifndef FILECOMPARATOR_H
#define FILECOMPARATOR_H

#include "ifilecomparator.h"

class FileComparator : public IFileComparator
{
public:
    FileComparator();

    // IFileComparer interface
    virtual bool areTheSame(QString filePath1, QString filePath2) override;
};

#endif // FILECOMPARATOR_H
