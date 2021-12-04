#include "maze.h"

Maze::Maze()
{
    height = 10;
    width = 10;
    initMap();
    fillEdgesWithWalls();
    map[getIndex(startPoint)] = start;
    coins = 0;
}

Maze::Maze(int h, int w){
    height = h;
    width = w;
    initMap();
    fillEdgesWithWalls();
    map[getIndex(startPoint)] = start;
    coins = 0;
}

Maze::Maze(int h, int w, QList<int> map){
    this->map = map;
    height = h;
    width = w;
    coins = 0;
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y ++){
            if(getObject(x, y) == coin){
                coins++;
            }
        }
    }
}

Maze::Maze(const Maze& other){
    height = other.height;
    width = other.width;
    coins = other.coins;
    map = other.map;
}

Maze& Maze::operator=(Maze other){
    std::swap(height, other.height);
    std::swap(width, other.width);
    std::swap(coins, other.coins);
    std::swap(map, other.map);
    return *this;
}

//edit maze methods
bool Maze::changeStartTo(int x, int y){
    //can not add outside of the map
    if(x >= width || y >= height || x < 0 || y < 0){
        return false;
    }
    if(getObject(x, y) == wall){
        return false;
    }
    objectAt(startPoint.x(), startPoint.y()) = space;
    startPoint = QPoint(x, y);
    objectAt(x, y) = start;
    return true;
}

bool Maze::addWall(int x, int y){
    //can not add outside of the map
    if(x >= width || y >= height || x < 0 || y < 0){
        return false;
    }
    //can not add wall on start point
    if(startPoint == QPoint(x, y)){
        return false;
    }
    //if the point is coin, remove the coin from map
    if(getObject(x, y) == coin){
        coins -= 1;
    }
    objectAt(x, y) = wall;
    return true;
}

bool Maze::addCoin(int x, int y){
    //can not add outside of the map
    if(x >= width || y >= height || x < 0 || y < 0){
        return false;
    }
    //can not add coin on wall
    if(getObject(x, y) == wall){
        return false;
    }
    objectAt(x, y) = coin;
    coins += 1;
    return true;
}

bool Maze::addSpace(int x, int y){
    //can not add outside of the map
    if(x >= width || y >= height || x < 0 || y < 0){
        return false;
    }
    //can not add space on edges
    if(x == 0 || x == width - 1){
        return false;
    }
    if(y == 0 || y == height - 1){
        return  false;
    }
    if(objectAt(x, y) == start){
        return false;
    }
    //if the point is coin, remove the coin from map
    if(getObject(x, y) == coin){
        coins -= 1;
    }
    objectAt(x, y) = space;
    return true;
}

//game play method
bool Maze::collectCoin(int x, int y){
    if(getObject(x, y) == coin){
        objectAt(x, y) = space;
        coins -= 1;
        return true;
    }
    return false;
}

bool Maze::coinClear(){
    return coins == 0;
}

//for saving to jason
QList<int> Maze::getMap(){
    return map;
}

int Maze::getHeight(){
    return height;
}

int Maze::getWidth(){
    return width;
}

//helper
int Maze::getIndex(QPoint point){
    return point.x() + point.y() * width;
}

void Maze::initMap(){
    for(int i = 0; i < height * width; i++){
        map.append(space);
    }
}

void Maze::fillEdgesWithWalls(){
    //fill top
    for(int i = 0; i < width; i ++){
        map[i] = wall;
    }
    //fill bottom
    for(int i = height * (width - 1); i < height * width; i ++){
        map[i] = wall;
    }
    //fill left
    for(int i = width; i < height * width; i += width){
        map[i] = wall;
    }
    //fill right
    for(int i = width - 1; i < height * width; i += width){
        map[i] = wall;
    }
}

int Maze::getObject(int x, int y){
    return map[getIndex(QPoint(x, y))];
}

int& Maze::objectAt(int x, int y){
    return map[getIndex(QPoint(x, y))];
}
