#ifndef FILESTATESCONSOLENOTIFIER_H
#define FILESTATESCONSOLENOTIFIER_H
#include <QObject>

class FileStatesConsoleNotifier: public QObject
{
Q_OBJECT
public slots:
    static void fileExistsNotify(const QString &path, qint64 size);
    static void fileModifiedNotify(const QString &path, qint64 size);
    static void fileNotExistsNotify(const QString &path);
    static void trackingEndedNotify(qint64 filesAmount);
};


#endif //FILESTATESCONSOLENOTIFIER_H
