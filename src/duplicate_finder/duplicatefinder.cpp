#include "duplicatefinder.h"

#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QDirIterator>
#include <QMap>

DuplicateFinder::DuplicateFinder(std::unique_ptr<IFileComparator> fileComparator) :
    m_fileComparator(std::move(fileComparator))
{
}

QList<QStringList> DuplicateFinder::getDuplicates(const QDir &dir, bool recursive)
{
    if (!dir.exists())
    {
        return QList<QStringList>();
    }

    QDirIterator::IteratorFlag iterFlag = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    QDirIterator dirIterator(dir.path(), QDir::Files, iterFlag);

    QMap<QString, QStringList> duplicateGroups;
    QStringList prevUniqueFiles;

    while (dirIterator.hasNext())
    {
        QString filePath = dirIterator.next();
        QString relativePath = dir.relativeFilePath(filePath);

        bool isDuplicate = false;

        for (auto prevFilePath : prevUniqueFiles)
        {
            if (m_fileComparator->areTheSame(filePath, prevFilePath))
            {
                duplicateGroups[prevFilePath].append(relativePath);
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate)
        {
            prevUniqueFiles.append(filePath);
        }
    }

    for (auto origFile : duplicateGroups.keys())
    {
        duplicateGroups[origFile].append(dir.relativeFilePath(origFile));
    }

    return duplicateGroups.values();
}
