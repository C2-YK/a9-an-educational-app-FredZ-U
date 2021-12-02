#ifndef BOT_H
#define BOT_H
#include <QList>
#include <QString>
#include <QPoint>
#include "box2d/b2_body.h"


class Bot
{
public:
    Bot();
    //methods for bot editing
    void addAction(int action);
    bool removeLastAction();
    bool compile();
    //methods for game mode
    void hit();
    int act();
    void reset();
    QPoint getDirection();
    const int Do = 0;
    const int UntilHit = 1;
    const int Forward = 2;
    const int Right = 3;
    const int Left = 4;
    const int noAction = 5;
    const QPoint dr_top = QPoint(0, 1);
    const QPoint dr_right = QPoint(1, 0);
    const QPoint dr_down = QPoint(0, -1);
    const QPoint dr_left = QPoint(-1, 0);
private:
    int actionPointer;
    bool hited;
    bool stop;
    QList<QPoint> directions;
    int direction = 0;
    const int maxLoopCount = 10;
    QList<int> loopHeads;
    QList<int> actions;

};

#endif // BOT_H
