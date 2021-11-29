#ifndef MAZE_H
#define MAZE_H
#include <QList>
#include <QPoint>

class Maze
{
public:
    Maze();
    //height and width must > 2
    Maze(int h, int w);
    //for loading form jason
    Maze(int h, int w, QList<int> map);
    //edit maze methods
    bool changeStartTo(int x, int y);
    bool addWall(int x, int y);
    bool addCoin(int x, int y);
    bool addSpace(int x, int y);
    //game play method

    //for saving to jason
    QList<int> getMap();
    int getHeight();
    int getWidth();
private:
    QPoint startPoint = QPoint(1, 1);
    int height;
    int width;
    int maxCoins;
    QList<int> map;
    int space = 0;
    int start = 1;
    int wall = 2;
    int coin = 3;
    //helper
    void fillEdgesWithWalls();
    int getIndex(QPoint postion);
    int getObject(int x, int y);
    int& objectAt(int x, int y);
};

#endif // MAZE_H
