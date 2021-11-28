#ifndef BOT_H
#define BOT_H
#include <QList>
#include <QString>
#include <QPoint>


class Bot
{
public:
    Bot();
    Bot(QPoint spawnPosition);
private:
    QList<QString*> actions;
    QPoint position;
    QString moveForward = "moveForward";
    QString turnRight = "turnRight";
    QString turnLeft = "turnLeft";
    QString loopString = "loopString";
};

#endif // BOT_H
