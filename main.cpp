#include <QCoreApplication>
#include <QTimer>
#include "FileStatesConsoleNotifier.h"
#include "FileStatesTracker.h"

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	FileStatesConsoleNotifier consoleNotifier;

	FileStatesTracker* tracker = nullptr;
	try {
		tracker = FileStatesTracker::getInstance();
	} catch (std::bad_alloc& exception) {
		cout << "Cannot allocate memory: " << exception.what() << endl;
	}

	QObject::connect(tracker,
		&FileStatesTracker::fileCreated,
		&consoleNotifier,
		&FileStatesConsoleNotifier::fileCreatedNotify);
	QObject::connect(tracker,
		&FileStatesTracker::fileModified,
		&consoleNotifier,
		&FileStatesConsoleNotifier::fileModifiedNotify);
	QObject::connect(tracker,
		&FileStatesTracker::fileDeleted,
		&consoleNotifier,
		&FileStatesConsoleNotifier::fileDeletedNotify);
	QObject::connect(tracker,
		&FileStatesTracker::fileTracked,
		&consoleNotifier,
		&FileStatesConsoleNotifier::fileTrackedNotify);
	QObject::connect(tracker,
		&FileStatesTracker::stopTracking,
		&consoleNotifier,
		&FileStatesConsoleNotifier::stopTrackingNotify);
	QObject::connect(tracker,
		&FileStatesTracker::fileAlreadyTracked,
		&consoleNotifier,
		&FileStatesConsoleNotifier::fileAlreadyTrackedNotify);
	QObject::connect(tracker,
		&FileStatesTracker::fileNotTracked,
		&consoleNotifier,
		&FileStatesConsoleNotifier::fileNotTrackedNotify);
	QObject::connect(tracker,
		&FileStatesTracker::fileNotModified,
		&consoleNotifier,
		&FileStatesConsoleNotifier::fileNotModifiedNotify);
	QObject::connect(tracker,
		&FileStatesTracker::trackingEnded,
		&consoleNotifier,
		&FileStatesConsoleNotifier::trackingEndedNotify);

	tracker->addFile(R"(../FilesToTrack/asd.txt)");
	tracker->addFile(R"(../FilesToTrack/asd2.txt)");
	tracker->addFile(R"(../FilesToTrack/asd2.txt)");
	tracker->addFile(R"(../FilesToTrack/asd3.txt)");
	tracker->deleteFile(R"(../FilesToTrack/asd3.txt)");
	tracker->deleteFile(R"(../FilesToTrack/notexistsinlist.txt)");
	cout << "-------------------------------Tracking started--------------------------------" << endl;

	QTimer timer;
	timer.setInterval(5000);
	QObject::connect(&timer, &QTimer::timeout, tracker, &FileStatesTracker::UpdateFileState);
	timer.start();

	int result = QCoreApplication::exec();

	delete tracker;

	return result;
}
