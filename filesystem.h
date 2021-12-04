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
    void setEditorMaze(Maze*);
    void setGamemodeMaze(Maze*);
public slots:
    bool loadMazeToEditor(QString);
    bool loadMazeToGamemode(QString);
    bool saveMazeToFile(QString);
signals:
    void loadCallback(bool);
    void saveCallback(bool);
private:
    Maze *editorMaze;
    Maze *gamemodeMaze;
    void mazeWriter(QJsonObject&);
    void mazeReader(const QJsonObject&, Maze&);


};

#endif // FILESYSTEM_H
