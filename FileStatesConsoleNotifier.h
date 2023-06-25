#pragma once
#include <QObject>
#include <iostream>

using namespace std;

class FileStatesConsoleNotifier : public QObject
{
 Q_OBJECT

 public:
	FileStatesConsoleNotifier(QObject* parent = nullptr);
	~FileStatesConsoleNotifier() = default;

 public slots:
	void fileTrackedNotify(string filePath, qint64 fileSize, bool isExist);
	void fileCreatedNotify(string filePath, qint64 fileSize);
	void fileModifiedNotify(string filePath, qint64 fileSize);
	void fileDeletedNotify(string filePath);
	void fileAlreadyTrackedNotify(string filePath);
	void fileNotTrackedNotify(string filePath);
	void stopTrackingNotify(string filePath);
	void fileNotModifiedNotify(string filePath);
	void trackingEndedNotify(int filesAmount);
};
