#include "FileStatesTracker.h"

FileStatesTracker* FileStatesTracker::instance = nullptr;

FileStatesTracker* FileStatesTracker::getInstance()
{
	if (instance == nullptr)
	{
		return instance = new FileStatesTracker();
	}

	return instance;
}

FileStatesTracker::~FileStatesTracker()
{
	instance->deleteLater();
	instance = nullptr;
}

FileStatesTracker::FileStatesTracker(QObject* parent) : QObject(parent)
{
}

void FileStatesTracker::addFile(QString filePath)
{
	if (filesToTrack.contains(filePath))
	{
		emit fileAlreadyTracked(filePath.toStdString());
	}
	else
	{
		filesToTrack.append(filePath);
		QFileInfo fileInfo(filePath);
		previousModification[fileInfo.filePath()] = fileInfo.lastModified();
		isFileExist[fileInfo.filePath()] = fileInfo.exists();
		emit fileTracked(fileInfo.filePath().toStdString(), fileInfo.size(), fileInfo.exists());
	}
}

void FileStatesTracker::deleteFile(QString filePath)
{
	if (!filesToTrack.contains(filePath))
	{
		emit fileNotTracked(filePath.toStdString());
	}
	else
	{
		filesToTrack.removeOne(filePath);
		previousModification.remove(filePath);
		isFileExist.remove(filePath);
		emit stopTracking(filePath.toStdString());
	}
}

void FileStatesTracker::UpdateFileState()
{
	for (const QString& filePath : filesToTrack)
	{
		QFileInfo file(filePath);
		if (file.exists() && !isFileExist[file.filePath()])
		{
			previousModification[file.filePath()] = file.lastModified();
			isFileExist[file.filePath()] = true;
			emit fileCreated(file.filePath().toStdString(), file.size());
		}
		else if (file.exists() && previousModification[file.filePath()] != file.lastModified())
		{
			previousModification[file.filePath()] = file.lastModified();
			emit fileModified(file.filePath().toStdString(), file.size());
		}
		else if (!file.exists() && isFileExist[file.filePath()])
		{
			previousModification.remove(file.filePath());
			isFileExist[file.filePath()] = false;
			emit fileDeleted(file.filePath().toStdString());
		}
		else
		{
			emit fileNotModified(file.filePath().toStdString());
		}
	}
	emit trackingEnded(filesToTrack.count());
}
