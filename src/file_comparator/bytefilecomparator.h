#ifndef BYTEFILECOMPARATOR_H
#define BYTEFILECOMPARATOR_H

#include "basefilecomparator.h"

class ByteFileComparator : public BaseFileComparator
{
public:
    ByteFileComparator();

    // IFileComparator interface
    virtual bool areTheSame(QString filePath1, QString filePath2) override;
};

#endif // BYTEFILECOMPARATOR_H
