#include "gamemode.h"

GameMode::GameMode()
{
    world = new b2World(b2Vec2(0, 0));
    connect(&timer, &QTimer::timeout, this, &GameMode::updateWorld);
}

void GameMode::start(){
    initGame();
    emit startEvent();
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
    qDebug()<<"init game";
    int w = masterMaze->getWidth();
    int h = masterMaze->getHeight();
    win = false;
    delete world;
    //create world
    world = new b2World(b2Vec2(0, 0));
    QList<b2Vec2> pos;
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            if(masterMaze->getObject(x, y) == masterMaze->wall){
                createWall(x * unitDistance, y * unitDistance);
            }else if(masterMaze->getObject(x, y) == masterMaze->start){
                createPlayer(x * unitDistance, y * unitDistance);
            }
            pos.append(b2Vec2(x * unitDistance, y * unitDistance));
        }
    }
    maze = *masterMaze; //make copy of master maze
    updateCount = 0;
    stoped = false;
    score = 0;
    bot->reset();
    emit setPlayerSize(playerSize);
    emit updatePlayerPosition(player->GetPosition());
    emit setMazeData(maze, pos, unitDistance);
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
    for(int i = 0; i < offsets.size(); i++){
        QPoint playerLoc = getMazeLocation(x + offsets[i], y+offsets[i]);
        if(maze.collectCoin(playerLoc.x(), playerLoc.y())){
            score++;
            emit setToSpace(playerLoc.x() + maze.getWidth() * playerLoc.y());
            emit updateCoins(score);
        }
    }
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
        emit winDisplay(true);
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
        prePlayerAction = action;
    }
    world->Step(1.0/60.0, 6, 2);
    trigger();
    if(player->GetPosition() == prePlayerPos && prePlayerAction == bot->Forward){
        qDebug()<<"hit";
        bot->hit();
    }
    prePlayerPos = player->GetPosition();
    emit updatePlayerPosition(player->GetPosition());
}
