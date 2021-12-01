#ifndef MAZEEDITOR_H
#define MAZEEDITOR_H

#include <QObject>

class MazeEditor : public QObject
{
    Q_OBJECT
public:
    MazeEditor();
public slots:
    void switchTool(int toolIndex);
    void resize(int height, int width);
    void useToolOn(QPoint position);
private:
    void addWall(QPoint position);
    void addSpace(QPoint position);
    void addCoin(QPoint position);
    void movePosition(QPoint position);

};
#endif // MAZEEDITOR_H
