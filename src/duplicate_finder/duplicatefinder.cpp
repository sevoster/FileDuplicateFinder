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

QList<QStringList> DuplicateFinder::getDuplicates(const QDir &dirLeft, const QDir &dirRight, bool recursive)
{
    if (!dirLeft.exists() || !dirRight.exists())
    {
        return QList<QStringList>();
    }

    QDirIterator::IteratorFlag iterFlag = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    QDirIterator dirLeftIterator(dirLeft.path(), QDir::Files, iterFlag);

    QList<QStringList> duplicateGroups;

    while (dirLeftIterator.hasNext())
    {
        QString leftFilePath = dirLeftIterator.next();
        QStringList newGroup;

        QDirIterator dirRightIterator(dirRight.path(), QDir::Files, iterFlag);

        while (dirRightIterator.hasNext())
        {
            QString rightFilePath = dirRightIterator.next();

            if (!m_fileComparator->areTheSame(leftFilePath, rightFilePath))
                continue;

            newGroup.append(rightFilePath);
        }

        if (!newGroup.empty())
        {
            newGroup.append(leftFilePath);
            duplicateGroups.append(newGroup);
        }
    }

    return duplicateGroups;
}
