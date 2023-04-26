#include "FileStatesConsoleNotifier.h"
#include <iostream>
using namespace std;

void FileStatesConsoleNotifier::fileNotExistsNotify(const QString &pathfile)
{
    cout << "File with the specified path " << pathfile.toStdString() << " does not exist" << endl;
}

void FileStatesConsoleNotifier::fileExistsNotify(const QString &pathfile, qint64 size)
{
    cout << "File with the specified path " << pathfile.toStdString() << " exists and has size of " << size << endl;
}

void FileStatesConsoleNotifier::fileModifiedNotify(const QString &pathfile, qint64 size)
{
    cout << "File with the specified path " << pathfile.toStdString() << " modified and has size of " << size << endl;
}

void FileStatesConsoleNotifier::trackingEndedNotify(qint64 filesAmount)
{
    cout << "----------------------Tracking ended with " << filesAmount << " files tracked----------------------"
         << endl;
}
