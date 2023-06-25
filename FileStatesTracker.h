#pragma once
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QList>
#include <QMap>

class FileStatesTracker : public QObject
{
 Q_OBJECT

 public:
	static FileStatesTracker* getInstance();
	~FileStatesTracker();
	void addFile(QString filePath);
	void deleteFile(QString filename);

 signals:
	void fileCreated(std::string filePath, qint64 fileSize);
	void fileDeleted(std::string filePath);
	void fileModified(std::string filePath, qint64 fileSize);
	void fileTracked(std::string filePath, qint64 fileSize, bool isExist);
	void stopTracking(std::string filePath);
	void fileNotTracked(std::string filePath);
	void fileAlreadyTracked(std::string filePath);
	void fileNotModified(std::string filePath);
	void trackingEnded(int filesAmount);

 public slots:
	void UpdateFileState();

 private:
	FileStatesTracker(QObject* parent = nullptr);
	static FileStatesTracker* instance;
	QList<QString> filesToTrack;
	QMap<QString, QDateTime> previousModification;
	QMap<QString, bool> isFileExist;
};
