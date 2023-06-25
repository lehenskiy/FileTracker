#include "FileStatesConsoleNotifier.h"

FileStatesConsoleNotifier::FileStatesConsoleNotifier(QObject* parent) : QObject(parent)
{
}

void FileStatesConsoleNotifier::fileTrackedNotify(string filePath, qint64 fileSize, bool isExist)
{
	if (isExist)
	{
		cout << "File was added for tracking: " << filePath << ", size: " << fileSize << "bytes" << endl;
	}
	else
	{
		cout << "File was added for tracking: " << filePath << ", It's not exist" << endl;
	}
}

void FileStatesConsoleNotifier::fileCreatedNotify(string filePath, qint64 fileSize)
{
	cout << "File was created: " << filePath << ", size: " << fileSize << "bytes" << endl;
}

void FileStatesConsoleNotifier::fileModifiedNotify(string filePath, qint64 fileSize)
{
	cout << "Existing file has been modified: " << filePath << ", size: " << fileSize << "bytes" << endl;
}

void FileStatesConsoleNotifier::fileDeletedNotify(string filePath)
{
	cout << "File was deleted: " << filePath << endl;
}

void FileStatesConsoleNotifier::stopTrackingNotify(string filePath)
{
	cout << "File " << filePath << " is no longer tracked" << endl;
}

void FileStatesConsoleNotifier::fileAlreadyTrackedNotify(string filePath)
{
	cout << "File " << filePath << " has already been added for tracking" << endl;
}

void FileStatesConsoleNotifier::fileNotTrackedNotify(string filePath)
{
	cout << "There is no such file for tracking to delete: " << filePath << endl;
}

void FileStatesConsoleNotifier::fileNotModifiedNotify(string filePath)
{
	cout << "File not changed from previous tracking: " << filePath << endl;
}

void FileStatesConsoleNotifier::trackingEndedNotify(int filesAmount)
{
	cout << "----------------------Tracking ended with " << filesAmount << " files tracked----------------------" << endl;
}
