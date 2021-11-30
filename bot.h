#ifndef BOT_H
#define BOT_H
#include <QList>
#include <QString>
#include <QPoint>


class Bot
{
public:
    Bot();
    //methods for bot editing
    void addAction(int action);
    void removeLastAction();
    bool compile();
    //methods for game mode
    void hit();
    int act();
    void reset();
    const int Do = 0;
    const int UntilHit = 1;
    const int Forward = 2;
    const int Right = 3;
    const int Left = 4;
    const int noAction = 5;
private:
    int actionPointer;
    bool hited;
    bool stop;
    const int maxLoopCount = 10;
    QList<int> loopHeads;
    QList<int> actions;

};

#endif // BOT_H
