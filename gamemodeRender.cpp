#include "gamemodeRender.h"

GameModeRender::GameModeRender()
{
    rendering = false;
    player.setColor(playerColor);
}

void GameModeRender::setMazeData(Maze m, QList<b2Vec2> p, float unitLength){
    maze.clear();
    QList<int> map = m.getMap();
    for(int i = 0; i < map.size(); i++){
        int x = (int) p[i].x * scale;
        int y = (int) p[i].y * scale;
        QPoint location = QPoint(x, y);
        if(map[i] == m.wall){
            maze.append(RenderObject(location, wallColor, (int)unitLength));
        }else if(map[i] == m.coin){
            maze.append(RenderObject(location, coinColor, (int)unitLength));
        }else if(map[i] == m.space){
            maze.append(RenderObject(location, spaceColor, (int)unitLength));
        }else if(map[i] == m.start){
            maze.append(RenderObject(location, startColor, (int)unitLength));
        }

    }
}

void GameModeRender::setPlayerPosition(const b2Vec2 pp){
    int x = (int) pp.x * scale;
    int y = (int) pp.y * scale;
    player.setLocation(QPoint(x, y));
}

void GameModeRender::setPlayerSize(float size){
    player.setSize((int) size * scale);
}

void GameModeRender::setToSpace(int index){
    maze[index].setColor(spaceColor);
}
