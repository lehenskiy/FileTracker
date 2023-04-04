#ifndef FILESCOLLECTION_H
#define FILESCOLLECTION_H

#include <QList>
#include <QString>

class FilesCollection
{
public:
    FilesCollection() = default;
    ~FilesCollection() = default;
    void add(QString pathfile) const;
    void remove(QString pathfile) const;
    QList<QString> getCollection() const { return this->collection; }
    void addFromFile(QString pathfile) const;

private:
    QList<QString> mutable collection;
};

#endif //FILESCOLLECTION_H
