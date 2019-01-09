#ifndef BASEFILECOMPARATOR_H
#define BASEFILECOMPARATOR_H

#include "ifilecomparator.h"

class BaseFileComparator : public IFileComparator
{
public:
    BaseFileComparator();

    // IFileComparator interface
    virtual bool areTheSame(QString filePath1, QString filePath2) override;
};

#endif // BASEFILECOMPARATOR_H
