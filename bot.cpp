#include "bot.h"
#include <box2d/box2d.h>
#include <QDebug>
Bot::Bot()
{
    reset();
    directions.append(dr_top);
    directions.append(dr_right);
    directions.append(dr_down);
    directions.append(dr_left);
}

//methods for bot editing
void Bot::addAction(int action){
    actions.append(action);
}

bool Bot::deleteAction(int index){
    if(actions.size() == 0)
        return false;
    if(index >= actions.size())
        return false;
    for(int i = index; i < actions.size() - 1; i++){
        actions[i] = actions[i + 1];
    }
    actions.pop_back();
    return true;
}

void Bot::clearActions(){
    actions = QList<int>();
}

bool Bot::compile(){
    QList<int> stack;
    for(int i = 0; i < actions.size(); i++){
        if(actions[i] == Do){
            stack.push_back(0);
        }else if(actions[i] == UntilHit){
            if(stack.size() == 0){
                return false;
            }
            stack.pop_back();
        }
    }
    return stack.size() == 0;
}

//methods for game mode
void Bot::hit(){
    hited = true;
}

int Bot::act(){
    if(actionPointer == actions.size()){
        stop = true;
    }
    if(stop){
        return noAction;
    }
    //read this action
    int action = actions[actionPointer];

    int loopCount = 0;//prevent endless loop
    //if action is Do or UntilHit
    //read next until the action is not Do or UntilHit
    while((action == Do || action == UntilHit) && !stop){
        if(action == Do){
            hited = false;
            loopHeads.append(actionPointer + 1);//memorize the index after Do
            actionPointer++;
            action = actions[actionPointer];
        }
        else if(action == UntilHit){
            if(hited){
                hited = false;
                loopHeads.pop_back();//clean the index on stack
                actionPointer++;
                if(actionPointer == actions.size()){
                    stop = true;
                }
                if(stop){
                    return noAction;
                }
                action = actions[actionPointer];
            }else{
                actionPointer = loopHeads[loopHeads.size() - 1];//back to the index on stack
                action = actions[actionPointer];
            }
        }

        loopCount++;
        //if the bot loop forever, stop the bot
        if(loopCount > maxLoopCount){
            stop = true;
            qDebug()<<"bot has stop";
            return noAction;
        }
    }
    actionPointer++;

    //change direction
    if(action == Left){
        direction++;
        if(direction == directions.size()){
            direction = 0;
        }
    }else if(action == Right){
        direction--;
        if(direction < 0){
            direction = directions.size() - 1;
        }
    }
    return action;
}

void Bot::reset(){
    actionPointer = 0;
    hited = false;
    stop = !compile();
    direction = 0;
}

QPoint Bot::getDirection(){
    return directions[direction];
}
