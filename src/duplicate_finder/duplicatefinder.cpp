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
    QList<QStringList> duplicateGroups;

    QDirIterator::IteratorFlag iterFlag = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    QDirIterator dirIterator(dirPath.path(), QDir::Files, iterFlag);

    while (dirIterator.hasNext())
    {
        QString filePath = dirIterator.next();
        QString relativePath = dirPath.relativeFilePath(filePath);

        auto foundIt = std::find_if(duplicateGroups.begin(), duplicateGroups.end(),
                                    [relativePath](const QStringList& group) { return group.contains(relativePath); });
        if (foundIt != duplicateGroups.end())
            continue;

        QStringList newDuplicateGroup;
        QDirIterator dirIteratorSecond(dirPath.path(), QDir::Files, iterFlag);
        while (dirIteratorSecond.hasNext())
        {
            QString secondFilePath = dirIteratorSecond.next();
            if (filePath == secondFilePath)
                continue;
            if (!m_fileComparator->areTheSame(filePath, secondFilePath))
                continue;
            newDuplicateGroup.append(dirPath.relativeFilePath(secondFilePath));
        }
        if (!newDuplicateGroup.empty())
        {
            newDuplicateGroup.append(relativePath);
            duplicateGroups.append(newDuplicateGroup);
        }
    }
    return duplicateGroups;
}
