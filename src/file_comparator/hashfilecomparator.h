#ifndef FILECOMPARATOR_H
#define FILECOMPARATOR_H

#include <QCryptographicHash>
#include "basefilecomparator.h"

class HashFileComparator : public BaseFileComparator
{
public:
    HashFileComparator(QCryptographicHash::Algorithm algorithm = QCryptographicHash::Sha1);

    // IFileComparer interface
    virtual bool areTheSame(QString filePath1, QString filePath2) override;

private:
    QCryptographicHash::Algorithm m_algorithm;
};

#endif // FILECOMPARATOR_H
