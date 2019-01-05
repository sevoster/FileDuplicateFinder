#ifndef DIRECTORYTRAVERSER_H
#define DIRECTORYTRAVERSER_H

#include "idirectorytraverser.h"

class DirectoryTraverser : public IDirectoryTraverser
{
public:
    DirectoryTraverser(const QString& directory, bool recusive);

    // IDirectoryTraverser interface
    virtual QList<QString> getFileNames() override;
    virtual void traverse() override;

private:
    QString m_dirPath;
    bool m_isRecursive;
    QList<QString> m_fileNames;
};

#endif // DIRECTORYTRAVERSER_H
