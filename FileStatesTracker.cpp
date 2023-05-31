#include "FileStatesTracker.h"
#include <QFileInfo>
#include <QDateTime>

FileStatesTracker* FileStatesTracker::instance = nullptr;

FileStatesTracker::~FileStatesTracker()
{
    delete instance;
    instance = nullptr;
}

FileStatesTracker* FileStatesTracker::getInstance()
{
    if (instance == nullptr) {
        instance = new FileStatesTracker();
    }

    return instance;
}

void FileStatesTracker::getFromPath(const QString &path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.exists()) {
        if (!previousModification.contains(path) || previousModification[path] == fileInfo.lastModified()) {
            emit fileExists(path, fileInfo.size());
        }
        else {
            emit fileModified(path, fileInfo.size());
        }
        previousModification[path] = fileInfo.lastModified();
    }
    else {
        emit fileNotExists(path);
    }
}

void FileStatesTracker::trackFromList(const QList<QString> &files)
{
    foreach(QString path, files) {
        this->getFromPath(path);
    }
    emit trackingEnded(files.count());
}
