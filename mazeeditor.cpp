#include "mazeeditor.h"

MazeEditor::MazeEditor()
{
    toolIndex = 0;
}
void MazeEditor::setMaze(Maze* target){
    this->target = target;
}
void MazeEditor::switchTool(int toolIndex){
    this->toolIndex = toolIndex;
}

void MazeEditor::useToolOn(QPoint position){
    if(position.x() >= target->getWidth() || position.x() < 0){
        return;
    }
    if(position.y() >= target->getHeight() || position.y() < 0){
        return;
    }
    if(toolIndex == 0){
        addSpace(position);
    }else if(toolIndex == 1){
        addWall(position);
    }else if(toolIndex==2){
        addCoin(position);
    }else{
        changeStartTo(position);
    }
    //xemit updatePreviewer();
}

void MazeEditor::reset(){
    *target = Maze();
}
/*
 * Private
 */

void MazeEditor::addWall(QPoint position){
    bool successed = target->addWall(position.x(), position.y());
    emit success("addWall",successed);
}
void MazeEditor::addSpace(QPoint position){
    bool successed = target->addSpace(position.x(), position.y());
    emit success("addSpace",successed);
}
void MazeEditor::addCoin(QPoint position){
    bool successed = target->addCoin(position.x(), position.y());
    emit success("addCoin",successed);
}
void MazeEditor::changeStartTo(QPoint position){
    bool successed = target -> changeStartTo(position.x(), position.y());
    emit success("changeStart",successed);
}


