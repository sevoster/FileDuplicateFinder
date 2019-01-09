#include "duplicatefinder.h"

#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QDirIterator>

DuplicateFinder::DuplicateFinder(const QDir &dirPath, bool recursive, IFileComparator *fileComparator) :
    m_dirPath(dirPath), m_isRecursive(recursive), m_fileComparator(fileComparator)
{
}

QList<QStringList> DuplicateFinder::getDuplicates()
{
    QList<QStringList> duplicates;
    QStringList looked;
    QDirIterator dirIterator(m_dirPath.path(), QDir::Files, m_isRecursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);

    while (dirIterator.hasNext())
    {
        QString filePath = dirIterator.next();
        if (looked.contains(filePath))
            continue;
        QStringList newDuplicatesList;
        QDirIterator dirIteratorSecond(m_dirPath.path(), QDir::Files, m_isRecursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);
        while (dirIteratorSecond.hasNext())
        {
            QString secondFilePath = dirIteratorSecond.next();
            if (filePath == secondFilePath)
                continue;
            if (!m_fileComparator->areTheSame(filePath, secondFilePath))
                continue;
            looked.append(secondFilePath);
            newDuplicatesList.append(m_dirPath.relativeFilePath(secondFilePath));
        }
        if (!newDuplicatesList.empty())
        {
            newDuplicatesList.append(m_dirPath.relativeFilePath(filePath));
            duplicates.append(newDuplicatesList);
        }
    }
    return duplicates;
}

QStringList DuplicateFinder::getFiles()
{
    return m_dirPath.entryList(QDir::Files);
}
