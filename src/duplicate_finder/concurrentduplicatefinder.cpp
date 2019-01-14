#include <QtConcurrent/QtConcurrentMap>
#include <QDirIterator>

#include "concurrentduplicatefinder.h"

QList<QFileInfo> getListOfFiles(const QDir& dir, bool recursive)
{
    QList<QFileInfo> files = dir.entryInfoList(QDir::Files);

    if (recursive)
    {
        QDirIterator iter(dir.path(), QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::IteratorFlag::Subdirectories);

        while (iter.hasNext()) {
            QString dirPath = iter.next();
            files.append(QDir(dirPath).entryInfoList(QDir::Files));
        }
    }

    return files;
}

struct InputParams
{
    IFileComparator* comparator;
    bool isRecursive;
    QDir rightDir;
};

struct Task
{
    QFileInfo leftFile;
    InputParams params;
};

struct MappedResult
{
    QFileInfo leftFile;
    QStringList duplicates;
};

MappedResult mappedFunc(const Task& task)
{
    QDirIterator rightDirIterator(task.params.rightDir.path(), QDir::Files,
                                  task.params.isRecursive ? QDirIterator::IteratorFlag::Subdirectories : QDirIterator::IteratorFlag::NoIteratorFlags);

    QStringList duplicates;

    while (rightDirIterator.hasNext()) {
        QString rightFile = rightDirIterator.next();

        if (!task.params.comparator->areTheSame(task.leftFile.absoluteFilePath(), rightFile))
            continue;

        duplicates.append(rightFile);
    }

    return { task.leftFile, duplicates };
}

void reduceFunc(QList<QPair<QString, QStringList>>& accumulator, const MappedResult& mappedResult)
{
    if (!mappedResult.duplicates.empty())
    {
        accumulator.append({mappedResult.leftFile.absoluteFilePath(), mappedResult.duplicates});
    }
}

ConcurrentDuplicateFinder::ConcurrentDuplicateFinder(std::unique_ptr<IFileComparator> fileComparator) : DuplicateFinder(std::move(fileComparator))
{

}

QList<QPair<QString, QStringList> > ConcurrentDuplicateFinder::getDuplicates(const QDir &dirLeft, const QDir &dirRight, bool recursive)
{
    InputParams params { m_fileComparator.get(), recursive, dirRight };

    QList<QFileInfo> leftFiles = getListOfFiles(dirLeft, recursive);
    QList<Task> tasks;

    for (auto file : leftFiles)
    {
        tasks.append({file, params});
    }

    return QtConcurrent::blockingMappedReduced(tasks, mappedFunc, reduceFunc);
}
