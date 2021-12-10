#include "gamemode.h"

GameMode::GameMode()
{
    world = new b2World(b2Vec2(0, 0));
}

void GameMode::start(){
    initGame();
    emit startEvent();
    connect(&timer, &QTimer::timeout, this, &GameMode::updateWorld);
    timer.start(timerStep);
}

void GameMode::setBot(Bot* b){
    bot = b;
}

void GameMode::setMaze(Maze* m){
    masterMaze = m;
}

void GameMode::stop(){
    stoped = true;
}

void GameMode::initGame(){
    int w = masterMaze->getWidth();
    int h = masterMaze->getHeight();
    win = false;
    //delete world;
    //create world
    //world = new b2World(b2Vec2(0, 0));
    QList<b2Vec2> pos;
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(masterMaze->getObject(x, y) == masterMaze->wall){
                createWall(x * unitDistance, y * unitDistance);
            }else if(masterMaze->getObject(x, y) == masterMaze->start){
                createPlayer(x * unitDistance, y * unitDistance);
            }
            pos.append(b2Vec2(x * unitDistance, y * unitDistance));
        }
    }
    maze = *masterMaze; //make copy of master maze
    maze.addCoin(2, 2);
    updateCount = 0;
    stoped = false;
    score = 0;
    bot->reset();
    emit setMazeData(maze, pos, unitDistance);
    emit setPlayerSize(playerSize);
}

void GameMode::createWall(float x, float y){
    b2BodyDef wallDef;
    wallDef.position.Set(x, y);
    b2Body* wallPos = world->CreateBody(&wallDef);
    b2PolygonShape box;
    box.SetAsBox(wallSize, wallSize);
    wallPos->CreateFixture(&box, 0.0f);
}

void GameMode::createPlayer(float x, float y){
    b2BodyDef botDef;
    botDef.type = b2_dynamicBody;
    botDef.position.Set(x, y);
    player = world->CreateBody(&botDef);
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
    if(maze.collectCoin(playerLoc.x(), playerLoc.y())){
        score++;
        emit setToSpace(playerLoc.x() + maze.getWidth() * playerLoc.y());
        emit updateCoins(score);
    }
    //collide check with moving direction
    QPoint dir = bot->getDirection();
    QPoint triggerDis = QPoint(dir.x()*triggerSensitive, dir.y()*triggerSensitive);
    QPoint tr = getMazeLocation(x + playerSize + triggerDis.x(), y + playerSize + triggerDis.y());
    QPoint tl = getMazeLocation(x - playerSize + triggerDis.x(), y + playerSize + triggerDis.y());
    QPoint br = getMazeLocation(x + playerSize + triggerDis.x(), y - playerSize + triggerDis.y());
    QPoint bl = getMazeLocation(x - playerSize + triggerDis.x(), y - playerSize + triggerDis.y());
    /*if(maze.getObject(tr.x(), tr.y()) == maze.wall
            || maze.getObject(tl.x(), tl.y()) == maze.wall
            || maze.getObject(bl.x(), bl.y()) == maze.wall
            || maze.getObject(br.x(), br.y()) == maze.wall ){
        bot->hit();
    }*/
}

void GameMode::checkWin(){
    win = maze.coinClear();
}

void GameMode::updateWorld(){
    if(stoped){
        timer.stop();
        emit stopEvent();
    }
    checkWin();
    if(win){
        timer.stop();
        qDebug()<<"win";
        emit winEvent();
    }
    updateCount++;
    if(updateCount >= botStep/timerStep){
        int action = bot->act();
        qDebug()<<action;
        //reset player movement
        player->SetLinearVelocity(b2Vec2(0, 0));
        if(action == bot->Forward){
            QPoint dir = bot->getDirection();
            player->SetLinearVelocity(b2Vec2(dir.x()*playerSpeed, dir.y()*playerSpeed));
        }else if(action == bot->Right){
            emit playRotateAnimation(1);
        }else if(action == bot->Left){
            emit playRotateAnimation(-1);
        }
        updateCount = 0;
    }
    world->Step(1.0/60.0, 6, 2);
    trigger();
    emit updatePlayerPosition(player->GetPosition());
}
