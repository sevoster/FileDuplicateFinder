#include <QtConcurrent/QtConcurrentMap>

#include "concurrentduplicatefinder.h"

QList<QDir> getAllDirsWithFiles(const QDir& parent)
{
    QList<QDir> dirs;

    QStringList subDirs = parent.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (auto subDir : subDirs)
        dirs.append(getAllDirsWithFiles(QDir(parent.absoluteFilePath(subDir))));

    if (!parent.isEmpty(QDir::Files))
        dirs.append(parent);

    return dirs;
}

struct InputParams
{
    IFileComparator* comparator;
    DuplicateFinder* finder;
};

struct Task
{
    QDir workDir;
    InputParams params;
};

struct MapResult
{
    QList<QStringList> duplicateGroups;
    InputParams params;
};

MapResult mappedFunc(const Task& task)
{
    return { task.params.finder->getDuplicates(task.workDir, false), task.params };
}

void reduceFunc(QList<QStringList>& accumulator, const MapResult& mapResult)
{
    for (auto group : mapResult.duplicateGroups)
    {
        QString& file = group.first();
        bool found = false;
        for (auto finalGroup : accumulator)
        {
            QString& finalFile = finalGroup.first();
            if (!mapResult.params.comparator->areTheSame(finalFile, file))
                continue;

            found = true;
            finalGroup.append(group);
        }

        if (!found)
            accumulator.append(group);
    }
}

ConcurrentDuplicateFinder::ConcurrentDuplicateFinder(std::unique_ptr<IFileComparator> fileComparator) : DuplicateFinder(std::move(fileComparator))
{

}

QList<QStringList> ConcurrentDuplicateFinder::getDuplicates(const QDir &dir, bool recursive)
{
    if (!recursive)
    {
        // Useless in non-recursive mode
        return DuplicateFinder::getDuplicates(dir, recursive);
    }

    InputParams params { m_fileComparator.get(), this };

    QList<QDir> dirs = getAllDirsWithFiles(dir);
    QList<Task> tasks;
    for (auto taskDir : dirs)
        tasks.append({ taskDir, params });

    return QtConcurrent::blockingMappedReduced(tasks, mappedFunc, reduceFunc);
}
