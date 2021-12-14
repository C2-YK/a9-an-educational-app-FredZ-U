#ifndef MAZEEDITOR_H
#define MAZEEDITOR_H
#include "maze.h"
#include <QObject>
#include <QPoint>
#include <QVector2D>
#include <QString>

class MazeEditor : public QObject
{
    Q_OBJECT
public:
    MazeEditor();
    void setMaze(Maze*);
public slots:
    void switchTool(int toolIndex);
    void useToolOn(QPoint position);
    void resize(int height, int width);
signals:
    void success(QString, bool);
private:
    Maze* target;
    int toolIndex;
    void addWall(QPoint position);
    void addSpace(QPoint position);
    void addCoin(QPoint position);
    void changeStartTo(QPoint position);

};
#endif // MAZEEDITOR_H
