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
    void stop();
    void initGame();
signals:
    void updatePlayerPosition(const b2Vec2& playerPos);
    void playRotateAnimation(int dir);// >0 clockwise <0 counter
    void setToSpace(int index);
    void updateCoins(int score);
    void setPlayerSize(float);
    void setMazeData(Maze, QList<b2Vec2>, float);
    void winEvent();
    void stopEvent();
    void startEvent();
private:
    Bot* bot;
    Maze* masterMaze;
    Maze maze;
    QTimer timer;
    bool win;
    bool stoped;
    int updateCount;
    int score;
    b2World* world;
    b2Vec2 prePlayerPos;
    int prePlayerAction;
    QList<b2Vec2> coinBodies;
    QList<b2Body*> wallBodies;
    b2Body* player;
    float wallSize = 10;
    //by def from box2d wall size is half length
    //in other word, it is the distance form center to edges
    //so unit distance between two walls should be 2 time wall size
    float unitDistance = 2 * wallSize;
    float playerSize = wallSize/2;
    QList<float> offsets = {0, 15};//offset for different between render and game
    float playerSpeed = 58;
    int timerStep = 50;
    int botStep = 1000;
    void createWall(float x, float y);
    void createPlayer(float x, float y);
    QPoint getMazeLocation(float x, float y);
    void trigger();
    void checkWin();
    void updateWorld();
};

#endif // GAMEMODE_H
