#include "directorytraverser.h"

#include <QDir>

DirectoryTraverser::DirectoryTraverser(const QString &directory, bool recusive) : m_dirPath(directory), m_isRecursive(recusive)
{
}

QList<QString> DirectoryTraverser::getFileNames()
{
    return m_fileNames;
}

void DirectoryTraverser::traverse()
{

}

