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


// Check the solution by finding a path way from the start point to coins
bool Maze::hasSolution()
{
    // If there exists no coins nor start, return false;
    if(!map.contains(start) || !map.contains(coin))
        return false;

    // record coins locations in the map
    QList<int> coinLocations;
    int coinIndex = 0;
    foreach(int mapInfo, map)
    {
        if(mapInfo == coin)
            coinLocations.append(coinIndex);
        coinIndex++;
    }
    // check if there is a path to the starter for each coin
    foreach(int coinIndex, coinLocations)
        if(isCoinToStart(coinIndex))
            return true;

    return false;
}

// For a certain coin, check if there exists a path to the starter.
// A helper method only for the hasSolution method.
bool Maze:: isCoinToStart(int coinIndex)
{

    int startIndex = map.indexOf(start);
    // make a copy
    QList<int> *copy = new QList<int>(map);

    QPoint coinPoint = converting(coinIndex);

    coloring(coinPoint,*copy);
    // after coloring, if they have the same value, then there exists a path between them.
    bool result = copy->at(startIndex) == covered;
    delete copy;

    return result;
}

// Using coloring way to find out a path from one point to another.
// p.y() represents the coordinate of y-axis; p.x() represent the coordinate of x-axis.
void Maze:: coloring(QPoint p, QList<int> &map)
{
    // if find a cycle, return
    if(map[getIndex(p)] == covered)
        return;
    else
    {
        // coloring
        map[getIndex(p)] = covered;
        // move around and prepare coloring
        QPoint moveToRight(1,0);
        if(!isOutOfRange(p+moveToRight))
        {
            QPoint rightIncrement = p + moveToRight;
            if(map[getIndex(rightIncrement)]!=wall)
                coloring(rightIncrement,map);
        }

        QPoint moveToLeft(-1,0);
        if(!isOutOfRange(p+moveToLeft))
        {
            QPoint leftIncrement = p + moveToLeft;
            if(map[getIndex(leftIncrement)]!=wall)
                coloring(leftIncrement,map);
        }

        QPoint moveToDown(0,1);
        if(!isOutOfRange(p+moveToDown))
        {
            QPoint downIncrement = p + moveToDown;
            if(map[getIndex(downIncrement)]!=wall)
                coloring(downIncrement,map);
        }

        QPoint moveToUp(0,-1);
        if(!isOutOfRange(p+moveToUp))
        {
            QPoint upIncrement = p + moveToUp;
            if(map[getIndex(upIncrement)]!=wall)
                coloring(upIncrement,map);
        }
    }
}

// Convert an int to a point.
QPoint Maze:: converting(int index)
{
    int y = index / width;
    int x = index % width;
    return QPoint(x,y);
}

// Check if the point p is in the map.
bool Maze:: isOutOfRange(QPoint p)
{
    return getIndex(p) >= height * width || getIndex(p) <= 0;
}

