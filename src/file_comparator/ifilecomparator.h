#ifndef IFILECOMPARATOR_H
#define IFILECOMPARATOR_H

#include <QString>

class IFileComparator
{
public:
    virtual ~IFileComparator() = default;
    virtual bool areTheSame(QString filePath1, QString filePath2) = 0;
};

#endif // IFILECOMPARATOR_H
