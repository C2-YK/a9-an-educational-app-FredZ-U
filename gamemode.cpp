#include "gamemode.h"

GameMode::GameMode() : world(b2Vec2(0, 0))
{
}

void GameMode::start(){

}

void GameMode::setBot(Bot*){

}

void GameMode::setMaze(Maze*){

}

void GameMode::initGame(){
    int w = masterMaze->getWidth();
    int h = masterMaze->getHeight();
    float x = 0;
    float y = 0;
    //create world
    world = b2World(b2Vec2(0, 0));
    for(int i = 0; i < h; i++){
        x = 0;
        for(int j = 0; j < w; j++){
            if(masterMaze->getObject(j, i) == masterMaze->wall){
                createWall(x, y);
            }else if(masterMaze->getObject(j, i) == masterMaze->start){
                createPlayer(x, y);
            }
            x -= unit;
        }
        y -= unit;
    }
    maze = *masterMaze; //make copy of master maze
}

void GameMode::createWall(float x, float y){
    b2BodyDef wallDef;
    wallDef.position.Set(x, y);
    b2Body* wallPos = world.CreateBody(&wallDef);
    b2PolygonShape box;
    box.SetAsBox(unit, unit);
    wallPos->CreateFixture(&box, 0.0f);
}

void GameMode::createPlayer(float x, float y){
    b2BodyDef botDef;
    botDef.type = b2_dynamicBody;
    botDef.position.Set(x, y);
    botBody = world.CreateBody(&botDef);
    b2PolygonShape box;
    box.SetAsBox(unit/2, unit/2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    botBody->CreateFixture(&fixtureDef);
}
