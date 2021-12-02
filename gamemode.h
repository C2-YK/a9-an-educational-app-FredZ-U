#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QObject>
#include <QList>
#include <QPoint>
#include <QTimer>
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
signals:
    void render(Maze maze, b2Vec2 playerPos);
private:
    Bot* bot;
    Maze* masterMaze;
    Maze maze;
    QTimer timer;
    bool win;
    b2World world;
    QList<b2Vec2> coinBodies;
    QList<b2Body*> wallBodies;
    b2Body* player;
    float wallSize = 10;
    //by def from box2d wall size is half length
    //in other word, it is the distance form center to edges
    //so unit distance between two walls should be 2 time wall size
    float unitDistance = 2 * wallSize;
    float playerSize = 5;
    float triggerSensitive = 0.1;
    void initGame();
    void createWall(float x, float y);
    void createPlayer(float x, float y);
    QPoint getMazeLocation(float x, float y);
    void trigger();
    void checkWin();
    void updateWorld();
};

#endif // GAMEMODE_H
