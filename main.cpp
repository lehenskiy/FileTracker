#include <QCoreApplication>
#include "FileStatesTracker.h"
#include "FileStatesConsoleNotifier.h"
#include "ListFormer.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileStatesTracker tracker = new FileStatesTracker();
    FileStatesConsoleNotifier *notifier = FileStatesConsoleNotifier::getInstance();

    QObject::connect(&tracker,
                     &FileStatesTracker::fileExists,
                     notifier,
                     &FileStatesConsoleNotifier::fileExistsNotify);
    QObject::connect(&tracker,
                     &FileStatesTracker::fileNotExists,
                     notifier,
                     &FileStatesConsoleNotifier::fileNotExistsNotify);
    QObject::connect(&tracker,
                     &FileStatesTracker::fileModified,
                     notifier,
                     &FileStatesConsoleNotifier::fileModifiedNotify);
    QObject::connect(&tracker,
                     &FileStatesTracker::trackingEnded,
                     notifier,
                     &FileStatesConsoleNotifier::trackingEndedNotify);

    QTimer timer;
    timer.setInterval(5000);
    QObject::connect(&timer, &QTimer::timeout, &tracker, [&tracker] {
        QList<QString> fileListToTrack = ListFormer::formFromFile(R"(../filesList.txt)");
        tracker.trackFromList(fileListToTrack);
    });
    timer.start();

    return QCoreApplication::exec();
}
