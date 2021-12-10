#include "gamemodeRender.h"
#include <QDebug>

GameModeRender::GameModeRender()
{
    rendering = false;
    //player.setColor(playerColor);
    player.setTexture(robotPix);
}

void GameModeRender::setMazeData(Maze m, QList<b2Vec2> p, float unitLength){
    maze.clear();
    sceneHeight = m.getHeight() * unitLength;
    sceneWidth = m.getWidth() * unitLength;
    QList<int> map = m.getMap();
    for(int i = 0; i < map.size(); i++){
        int x = (int) (p[i].x - unitLength/2) * scale+10;
        int y = (int) (p[i].y - unitLength/2) * scale+10;
        QPoint location = QPoint(x, y);
        if(map[i] == m.wall){
            maze.append(RenderObject(location, wallColor, (int)unitLength));
            maze[maze.size()-1].setTexture(wallPix);
            //qDebug();
           maze[maze.size()-1].hasTexture = true;
        }else if(map[i] == m.coin){
            maze.append(RenderObject(location, coinColor, (int)unitLength));
            maze[maze.size()-1].setTexture(coinPix);
            maze[maze.size()-1].hasTexture = true;
        }else if(map[i] == m.space){
            maze.append(RenderObject(location, spaceColor, (int)unitLength));

        }/*else if(map[i] == m.start){
            maze.append(RenderObject(location, startColor, (int)unitLength));
        }*/

    }
}

void GameModeRender::setPlayerPosition(b2Vec2 pp){
    int x = (int) (pp.x - player.getSize()/2) * scale+2;
    int y = (int) (pp.y - player.getSize()/2) * scale+2;

    player.setLocation(QPoint(x, y));
}

void GameModeRender::setPlayerSize(float size){
    player.setSize((int) size * scale);
}

void GameModeRender::setToSpace(int index){
    maze[index].setColor(spaceColor);
}

void GameModeRender::startRender(){
    if(!rendering){
        rendering = true;
        render();
    }
}

void GameModeRender::stopRender(){
    rendering = false;
}

void GameModeRender::render(){
    if(!rendering){
        return;
    }
    scene = QPixmap(sceneWidth, sceneHeight);
    scene.fill(QColor("transparent"));
    QPainter p = QPainter(&scene);
    for(int i = 0; i < maze.size(); i++){
        if(maze[i].hasTexture){
              //qDebug() << i;
            //used to be fillRect
           p.drawPixmap(maze[i].getLocation().x(), maze[i].getLocation().y(), maze[i].getSize(), maze[i].getSize(), maze[i].getTexture());

        }
        else{
            // qDebug() << i;
            p.fillRect(maze[i].getLocation().x(), maze[i].getLocation().y(),maze[i].getSize(), maze[i].getSize(), maze[i].getColor());

        }
    } 
    //It used to be fillRect
    p.drawPixmap(player.getLocation().x(), player.getLocation().y(), player.getSize(), player.getSize(), player.getTexture());
    emit updateScene(scene);
    QTimer::singleShot(1000/FPS, this, SLOT(render()));
}
