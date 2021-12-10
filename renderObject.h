#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H
#include <QPoint>
#include <QImage>
#include <QColor>


class RenderObject
{
public:
    RenderObject();
    RenderObject(QPoint location, QColor color, int size);
    bool hasTexture;
    QPoint getLocation();
    void setLocation(QPoint location);
    QColor getColor();
    void setColor(QColor color);
    int getSize();
    void setSize(int size);
    void setTexture(QImage*);
    const QImage& getTexture();
private:
    QPoint location;
    QColor color;
    int size;
    QImage* texture;
};

#endif // RENDEROBJECT_H
