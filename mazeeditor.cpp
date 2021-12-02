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
        movePosition(position);
    }
    //xemit updatePreviewer();
}
/*
 * Private
 */

void MazeEditor::addWall(QPoint position){
    target->addWall(position.x(), position.y());
}
void MazeEditor::addSpace(QPoint position){
    target->addSpace(position.x(), position.y());
}
void MazeEditor::addCoin(QPoint position){
    target->addCoin(position.x(), position.y());
}
void MazeEditor::movePosition(QPoint position){

}


