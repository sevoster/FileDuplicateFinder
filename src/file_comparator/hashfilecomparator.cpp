#include <QCryptographicHash>
#include <QFile>

#include "hashfilecomparator.h"

HashFileComparator::HashFileComparator(QCryptographicHash::Algorithm algorithm) : m_algorithm(algorithm)
{
}

bool HashFileComparator::areTheSame(QString filePath1, QString filePath2)
{
    if (!BaseFileComparator::areTheSame(filePath1, filePath2))
    {
        return false;
    }

    QFile file1(filePath1);
    QFile file2(filePath2);
    file1.open(QIODevice::ReadOnly);
    file2.open(QIODevice::ReadOnly);

    QCryptographicHash hash1(m_algorithm);
    QCryptographicHash hash2(m_algorithm);
    hash1.addData(file1.readAll());
    hash2.addData(file2.readAll());

    return hash1.result() == hash2.result();
}
