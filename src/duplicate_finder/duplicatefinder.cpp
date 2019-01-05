#include "duplicatefinder.h"

#include <QDir>
#include <QFileInfo>

DuplicateFinder::DuplicateFinder(const QString &dirPath, bool recursive) : m_dirPath(dirPath), m_isRecursive(recursive)
{
}

QStringList DuplicateFinder::getDuplicates()
{
    QStringList duplicates;
    QStringList files = getFiles();
    for (auto it = files.begin(); it + 1 != files.end(); it++)
    {
        QFileInfo fileInfo(QDir(m_dirPath), *it);
        for (auto it2 = it + 1; it2 != files.end(); it2++)
        {
            QFileInfo fileInfo2(QDir(m_dirPath), *it2);
            if (fileInfo.size() != fileInfo2.size())
                continue;
            duplicates.append(*it2);
        }
    }
    return duplicates;
}

QStringList DuplicateFinder::getFiles()
{
    QDir dir(m_dirPath);
    return dir.entryList(QDir::Files);
}
