#ifndef BOT_H
#define BOT_H
#include <QList>
#include <QString>
#include <QPoint>


class Bot
{
public:
    Bot();
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
    bool end;
    const int maxLoopCount = 10;
    QList<int> stack;
    QList<int> actions;
    bool compile();

};

#endif // BOT_H
