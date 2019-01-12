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

    if (!file1.exists() || !file2.exists())
    {
        throw std::runtime_error("Files do not exist");
    }

    if (!file1.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Failed to open files");
    }

    QCryptographicHash hash1(m_algorithm);
    QCryptographicHash hash2(m_algorithm);
    hash1.addData(file1.readAll());
    hash2.addData(file2.readAll());

    return hash1.result() == hash2.result();
}
