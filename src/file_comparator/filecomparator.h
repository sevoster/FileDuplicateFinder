#ifndef FILECOMPARER_H
#define FILECOMPARER_H

#include "ifilecomparator.h"

class FileComparator : public IFileComparator
{
public:
    FileComparator();

    // IFileComparer interface
    virtual bool areTheSame(QString filePath1, QString filePath2) override;
};

#endif // FILECOMPARER_H
