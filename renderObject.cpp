#include "renderObject.h"

RenderObject::RenderObject()
{
    hasTexture = false;
}

QPoint RenderObject::getLocation(){
    return location;
}

void RenderObject::setLocation(QPoint location){
    this->location = location;
}

QColor RenderObject::getColor(){
    return color;
}

void RenderObject::setColor(QColor color){
    this->color = color;
}

int RenderObject::getSize(){
    return size;
}

void RenderObject::setSize(int size){
    this->size = size;
}

const QImage& RenderObject::getTexture(){
    return *texture;
}
