#include "gamemode.h"

GameMode::GameMode() : world(b2Vec2(0, 0))
{
}

void GameMode::start(){
    initGame();
    connect(&timer, &QTimer::timeout, this, &GameMode::updateWorld);
    timer.start(50);
}

void GameMode::setBot(Bot* b){
    bot = b;
}

void GameMode::setMaze(Maze* m){
    masterMaze = m;
}

void GameMode::initGame(){
    int w = masterMaze->getWidth();
    int h = masterMaze->getHeight();
    win = false;
    //create world
    world = b2World(b2Vec2(0, 0));
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(masterMaze->getObject(x, y) == masterMaze->wall){
                createWall(x * unitDistance, y * unitDistance);
            }else if(masterMaze->getObject(x, y) == masterMaze->start){
                createPlayer(x * unitDistance, y * unitDistance);
            }
        }
    }
    maze = *masterMaze; //make copy of master maze
}

void GameMode::createWall(float x, float y){
    b2BodyDef wallDef;
    wallDef.position.Set(x, y);
    b2Body* wallPos = world.CreateBody(&wallDef);
    b2PolygonShape box;
    box.SetAsBox(wallSize, wallSize);
    wallPos->CreateFixture(&box, 0.0f);
}

void GameMode::createPlayer(float x, float y){
    b2BodyDef botDef;
    botDef.type = b2_dynamicBody;
    botDef.position.Set(x, y);
    player = world.CreateBody(&botDef);
    b2PolygonShape box;
    box.SetAsBox(playerSize, playerSize);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    player->CreateFixture(&fixtureDef);
}

QPoint GameMode::getMazeLocation(float x, float y){
    int i = (int)(x/unitDistance);
    int j = (int)(y/unitDistance);
    return QPoint(i, j);
}

void GameMode::trigger(){
    float x = player->GetPosition().x;
    float y = player->GetPosition().y;
    //collect this locations coin if have any
    QPoint playerLoc = getMazeLocation(x, y);
    maze.collectCoin(playerLoc.x(), playerLoc.y());
    //collide check with moving direction
    QPoint dir = bot->getDirection();
    QPoint triggerDis = QPoint(dir.x()*triggerSensitive, dir.y()*triggerSensitive);
    QPoint tr = getMazeLocation(x + playerSize + triggerDis.x(), y + playerSize + triggerDis.y());
    QPoint tl = getMazeLocation(x - playerSize + triggerDis.x(), y + playerSize + triggerDis.y());
    QPoint br = getMazeLocation(x + playerSize + triggerDis.x(), y - playerSize + triggerDis.y());
    QPoint bl = getMazeLocation(x - playerSize + triggerDis.x(), y - playerSize + triggerDis.y());
    if(maze.getObject(tr.x(), tr.y()) == maze.wall
            || maze.getObject(tl.x(), tl.y()) == maze.wall
            || maze.getObject(bl.x(), bl.y()) == maze.wall
            || maze.getObject(br.x(), br.y()) == maze.wall ){
        bot->hit();
    }
}

void GameMode::checkWin(){
    win = maze.clear();
}

void GameMode::updateWorld(){
    world.Step(1.0/60.0, 6, 2);
}
