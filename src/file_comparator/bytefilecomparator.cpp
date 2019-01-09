#include <algorithm>
#include <fstream>

#include "bytefilecomparator.h"

ByteFileComparator::ByteFileComparator()
{

}

bool ByteFileComparator::areTheSame(QString filePath1, QString filePath2)
{
    if (!BaseFileComparator::areTheSame(filePath1, filePath2))
    {
        return false;
    }

    std::ifstream file1(filePath1.toStdString());
    std::ifstream file2(filePath2.toStdString());

    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);

    std::istreambuf_iterator<char> end;

    return std::equal(begin1, end, begin2);
}
