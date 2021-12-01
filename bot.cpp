#include "bot.h"
#include <box2d/box2d.h>
Bot::Bot()
{
    actions.append(noAction);
    reset();
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 20.0f);


}

//methods for bot editing
void Bot::addAction(int action){
    actions.append(action);
}

bool Bot::removeLastAction(){
    if(actions.size() == 0){
        return false;
    }
    actions.pop_back();
    return true;
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
                action = actions[actionPointer];
            }else{
                actionPointer = loopHeads[loopHeads.size() - 1];//back to the index on stack
            }
        }

        loopCount++;
        //if the bot loop forever, stop the bot
        if(loopCount > maxLoopCount){
            stop = true;
            return noAction;
        }
    }
    actionPointer++;
    return action;
}

void Bot::reset(){
    actionPointer = 0;
    hited = false;
    stop = compile();
}
