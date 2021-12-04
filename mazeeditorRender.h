#ifndef MAZEEDITORRENDER_H
#define MAZEEDITORRENDER_H

#include <QObject>
#include "maze.h"

class MazeEditorRender : public QObject
{
    Q_OBJECT
public:
    MazeEditorRender();
    void setMaze(Maze*);
private:
    Maze* maze;
};

#endif // MAZEEDITORRENDER_H
