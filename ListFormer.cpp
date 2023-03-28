#include "ListFormer.h"
#include <QFile>
#include <QTextStream>

QList<QString> ListFormer::formFromFile(QString pathfile)
{
    QList<QString> resultList;

    QFile sourceFile(pathfile);
    sourceFile.open(QIODevice::ReadOnly);
    QTextStream sourceStream(&sourceFile);

    while (!sourceStream.atEnd()) {
        resultList.append(sourceStream.readLine());
    }
    sourceFile.close();

    return resultList;
}
