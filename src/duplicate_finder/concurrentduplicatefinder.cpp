#include <QtConcurrent/QtConcurrentMap>
#include <QDirIterator>

#include "concurrentduplicatefinder.h"

QStringList getListOfFiles(const QDir& dir, bool recursive)
{
    QStringList files = dir.entryList(QDir::Files);

    for (QString& file : files)
    {
        file = dir.absoluteFilePath(file);
    }

    if (recursive)
    {
        QDirIterator iter(dir.path(), QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::IteratorFlag::Subdirectories);

        while (iter.hasNext()) {
            QString dirPath = iter.next();
            files.append(getListOfFiles(QDir(dirPath), recursive));
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
    QString leftFilePath;
    InputParams params;
};

QStringList mappedFunc(const Task& task)
{
    QDirIterator rightDirIterator(task.params.rightDir.path(), QDir::Files, task.params.isRecursive ? QDirIterator::IteratorFlag::Subdirectories : QDirIterator::IteratorFlag::NoIteratorFlags);

    QStringList duplicates;

    while (rightDirIterator.hasNext()) {
        QString rightFile = rightDirIterator.next();

        if (!task.params.comparator->areTheSame(task.leftFilePath, rightFile))
            continue;

        duplicates.append(rightFile);
    }

    if (!duplicates.empty())
    {
        duplicates.append(task.leftFilePath);
    }

    return duplicates;
}

void reduceFunc(QList<QStringList>& accumulator, const QStringList& duplicateGroups)
{
    if (!duplicateGroups.empty())
    {
        accumulator.append(duplicateGroups);
    }
}

ConcurrentDuplicateFinder::ConcurrentDuplicateFinder(std::unique_ptr<IFileComparator> fileComparator) : DuplicateFinder(std::move(fileComparator))
{

}

QList<QStringList> ConcurrentDuplicateFinder::getDuplicates(const QDir &dirLeft, const QDir &dirRight, bool recursive)
{
    InputParams params { m_fileComparator.get(), recursive, dirRight };

    QStringList leftFiles = getListOfFiles(dirLeft, recursive);
    QList<Task> tasks;

    for (auto file : leftFiles)
    {
        tasks.append({file, params});
    }

    return QtConcurrent::blockingMappedReduced(tasks, mappedFunc, reduceFunc);
}
