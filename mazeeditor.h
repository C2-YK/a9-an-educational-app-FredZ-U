#ifndef MAZEEDITOR_H
#define MAZEEDITOR_H
#include "maze.h"
#include <QObject>
#include <QPoint>
#include <QVector2D>

class MazeEditor : public QObject
{
    Q_OBJECT
public:
    MazeEditor();
    void setMaze(Maze*);
public slots:
    void switchTool(int toolIndex);
    void useToolOn(QPoint position);
private:
    Maze* target;
    int toolIndex;
    void addWall(QPoint position);
    void addSpace(QPoint position);
    void addCoin(QPoint position);
    void movePosition(QPoint position);

};
#endif // MAZEEDITOR_H
