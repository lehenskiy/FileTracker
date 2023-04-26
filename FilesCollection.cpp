#include "FilesCollection.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>

void FilesCollection::add(QString pathfile) const
{
    if (!this->collection.contains(pathfile)) {
        this->collection.append(pathfile);
    }
}

void FilesCollection::remove(QString pathfile) const
{
    if (this->collection.contains(pathfile)) {
        this->collection.removeOne(pathfile);
    }
}

void FilesCollection::addFromFile(QString pathfile) const
{
    QFile sourceFile(pathfile);
    if (!sourceFile.exists()) {
        throw std::runtime_error("File does not exist");
    }

    sourceFile.open(QIODevice::ReadOnly);
    QTextStream sourceStream(&sourceFile);

    while (!sourceStream.atEnd()) {
        this->add(sourceStream.readLine());
    }
    sourceFile.close();
}