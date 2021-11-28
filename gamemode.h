#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QObject>
#include "maze.h"
#include "bot.h"

class GameMode
{
    Q_OBJECT
public:
    GameMode();
public slots:
    void start();
    void setBot(Bot*);
    void setMaze(Maze*);
private:
    Bot* playerBot;
    Maze* maze;
};

#endif // GAMEMODE_H
