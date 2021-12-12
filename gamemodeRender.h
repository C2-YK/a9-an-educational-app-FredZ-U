#ifndef GAMEMODERENDER_H
#define GAMEMODERENDER_H

#include <QObject>
#include <QColor>
#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
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
    void stopRender();
    void renderLoop();
    void render();
    void setMazeData(Maze, QList<b2Vec2>, float);
    void setPlayerPosition(b2Vec2 pp);
    void setPlayerSize(float);
    void setToSpace(int index);
signals:
    void updateScene(const QPixmap& scene);
private:
    const QColor wallColor = QColor(0, 0, 0, 255);
    const QColor coinColor = QColor(255, 255, 0, 255);
    const QColor spaceColor = QColor(255, 255, 255, 255);
    const QColor startColor = QColor(0, 255, 255, 255);
    const QColor playerColor = QColor(0, 0, 255, 255);
    QPixmap *wallPix = new QPixmap(":/icon/res/wall.png");
    QPixmap *coinPix = new QPixmap(":/icon/res/coin.png");
    QPixmap *robotPix = new QPixmap(":/icon/res/robot.png");
    QPixmap *blockPix = new QPixmap(":/icon/res/block.png");
    QList<RenderObject> maze;
    RenderObject player;
    QPixmap scene;
    int scale = 1;
    int FPS = 30;
    int sceneWidth;
    int sceneHeight;
    bool rendering = false;
};

#endif // GAMEMODERENDER_H
