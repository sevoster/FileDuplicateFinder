#include <QFileInfo>

#include "basefilecomparator.h"

BaseFileComparator::BaseFileComparator()
{

}

bool BaseFileComparator::areTheSame(QString filePath1, QString filePath2)
{
    QFileInfo fileInfo1(filePath1);
    QFileInfo fileInfo2(filePath2);

    return fileInfo1.size() == fileInfo2.size();
}
