#ifndef IDIRECTORYTRAVERSER_H
#define IDIRECTORYTRAVERSER_H

#include <QList>
#include <QString>

class IDirectoryTraverser
{
public:
    virtual ~IDirectoryTraverser() = default;
    virtual void traverse() = 0;
    virtual QList<QString> getFileNames() = 0;
};

#endif // IDIRECTORYTRAVERSER_H
