#ifndef LISTFORMER_H
#define LISTFORMER_H

#include <QList>
#include <QString>

class ListFormer
{
public:
    ListFormer() = default;
    ~ListFormer() = default;
    static QList<QString> formFromFile(QString pathfile);
};

#endif //LISTFORMER_H
