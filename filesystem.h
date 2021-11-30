#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "maze.h"

class FileSystem : public QObject
{
    Q_OBJECT
public:
    FileSystem();
    bool loadMazeFromFile(QString);
    bool saveMazeToFile(QString);
private:
    Maze *maze;
    void mazeWriter(QJsonObject&);
    Maze mazeReader(QJsonObject&);


};

#endif // FILESYSTEM_H
