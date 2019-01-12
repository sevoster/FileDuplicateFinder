#include "duplicatefinder.h"

#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QDirIterator>

DuplicateFinder::DuplicateFinder(std::unique_ptr<IFileComparator> fileComparator) :
    m_fileComparator(std::move(fileComparator))
{
}

QList<QStringList> DuplicateFinder::getDuplicates(const QDir &dirPath, bool recursive)
{
    QList<QStringList> duplicates;
    QStringList looked;
    QDirIterator::IteratorFlag iterFlag = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    QDirIterator dirIterator(dirPath.path(), QDir::Files, iterFlag);

    while (dirIterator.hasNext())
    {
        QString filePath = dirIterator.next();
        if (looked.contains(filePath))
            continue;
        QStringList newDuplicatesList;
        QDirIterator dirIteratorSecond(dirPath.path(), QDir::Files, iterFlag);
        while (dirIteratorSecond.hasNext())
        {
            QString secondFilePath = dirIteratorSecond.next();
            if (filePath == secondFilePath)
                continue;
            if (!m_fileComparator->areTheSame(filePath, secondFilePath))
                continue;
            looked.append(secondFilePath);
            newDuplicatesList.append(dirPath.relativeFilePath(secondFilePath));
        }
        if (!newDuplicatesList.empty())
        {
            newDuplicatesList.append(dirPath.relativeFilePath(filePath));
            duplicates.append(newDuplicatesList);
        }
    }
    return duplicates;
}
