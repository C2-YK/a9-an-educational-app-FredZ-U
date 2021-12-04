#ifndef GAMEMODERENDER_H
#define GAMEMODERENDER_H

#include <QObject>
#include <QColor>
#include <QList>
#include <QPoint>
#include "renderObject.h"
#include "maze.h"
#include "box2d/b2_body.h"

class GameModeRender : public QObject
{
    Q_OBJECT
public:
    GameModeRender();
public slots:
    void startRender();
    void setMazeData(Maze, QList<b2Vec2>, float);
    void setPlayerPosition(const b2Vec2);
    void setPlayerSize(float);
    void setToSpace(int index);
signals:
    void renderMaze(const QList<RenderObject>&);
    void renderPlayer(const RenderObject& player);
private:
    const QColor wallColor = QColor(0, 0, 0, 255);
    const QColor coinColor = QColor(255, 255, 0, 255);
    const QColor spaceColor = QColor(255, 255, 255, 255);
    const QColor startColor = QColor(0, 255, 255, 255);
    const QColor playerColor = QColor(0, 0, 255, 255);
    QList<RenderObject> maze;
    RenderObject player;
    int scale = 20;
    bool rendering = false;
};

#endif // GAMEMODERENDER_H
