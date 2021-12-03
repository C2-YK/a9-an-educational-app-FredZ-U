#ifndef GAMEMODERENDER_H
#define GAMEMODERENDER_H

#include <QObject>
#include <QColor>
#include "renderObject.h"

class GameModeRender : public QObject
{
    Q_OBJECT
public:
    GameModeRender();
private:
    const QColor wallColor = QColor(0, 0, 0, 255);
    const QColor coinColor = QColor(255, 255, 0, 255);
    const QColor spaceColor = QColor(255, 255, 255, 255);
    const QColor playerColor = QColor(0, 0, 255, 255);
};

#endif // GAMEMODERENDER_H
