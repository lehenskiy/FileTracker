#include <QCoreApplication>
#include "FileStatesTracker.h"
#include "FileStatesConsoleNotifier.h"
#include "FilesCollection.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileStatesTracker* tracker = FileStatesTracker::getInstance();
    FilesCollection filesCollection;
    if (tracker == nullptr) {
        QCoreApplication::exit();
    }

    QObject::connect(tracker,
                     &FileStatesTracker::fileExists,
                     &FileStatesConsoleNotifier::fileExistsNotify);
    QObject::connect(tracker,
                     &FileStatesTracker::fileNotExists,
                     &FileStatesConsoleNotifier::fileNotExistsNotify);
    QObject::connect(tracker,
                     &FileStatesTracker::fileModified,
                     &FileStatesConsoleNotifier::fileModifiedNotify);
    QObject::connect(tracker,
                     &FileStatesTracker::trackingEnded,
                     &FileStatesConsoleNotifier::trackingEndedNotify);

    QTimer timer;
    timer.setInterval(5000);
    QObject::connect(&timer, &QTimer::timeout, tracker, [tracker, filesCollection] {
        filesCollection.addFromFile(R"(../filesList.txt)");
        filesCollection.add(R"(../filesList.txt)");
        filesCollection.remove(R"(C:\Example\Path\To\file.txt)");
        QList<QString> fileListToTrack = filesCollection.getCollection();

        tracker->trackFromList(fileListToTrack);
    });
    timer.start();

    int result = QCoreApplication::exec();

    delete tracker;
    delete &filesCollection;

    return result;
}
