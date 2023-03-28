#ifndef FILETRACKER_FILESTATESTRACKER_H
#define FILETRACKER_FILESTATESTRACKER_H

#include <QObject>
#include <QMap>

class FileStatesTracker: public QObject
{
Q_OBJECT

public:
    FileStatesTracker(QObject *parent = nullptr);
    ~FileStatesTracker();

public slots:
    void getFromPath(const QString &path);
    void trackFromList(const QList<QString> &files);

signals:
    void fileExists(QString path, qint64 size);
    void fileModified(QString path, qint64 size);
    void fileNotExists(QString path);
    void trackingEnded(qint64 filesAmount);

private:
    QMap<QString, QDateTime> previousModification;
};


#endif //FILETRACKER_FILESTATESTRACKER_H
