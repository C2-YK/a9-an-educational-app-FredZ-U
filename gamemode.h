#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QObject>
#include <QList>
#include <box2d/box2d.h>
#include "maze.h"
#include "bot.h"

class GameMode : public QObject
{
    Q_OBJECT
public:
    GameMode();
public slots:
    void start();
    void setBot(Bot*);
    void setMaze(Maze*);
private:
    Bot* bot;
    Maze* masterMaze;
    Maze maze;
    b2World world;
    QList<b2Vec2> coinBodies;
    QList<b2Body*> wallBodies;
    b2Body* botBody;
    float unit = 10;
    void initGame();
    void createWall(float x, float y);
    void createPlayer(float x, float y);
};

#endif // GAMEMODE_H
