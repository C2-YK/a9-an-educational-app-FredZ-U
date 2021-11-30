#include "bot.h"

Bot::Bot()
{
    actions.append(noAction);
    reset();
}

void Bot::hit(){
    hited = true;
}

int Bot::act(){
    if(end){
        return noAction;
    }
    //read this action
    int action = actions[actionPointer];

    int loopCount = 0;//prevent endless loop
    while((action == Do || action == UntilHit) && !end){
        if(action == Do){
            stack.append(actionPointer + 1);
            actionPointer++;
            action = actions[actionPointer];
        }
        if(action == UntilHit){
            if(hited){
                hited = false;
                stack.pop_back();
                actionPointer++;
            }else{
                actionPointer = stack[stack.size() - 1];
            }
        }

        loopCount++;
        //if the bot loop forever, stop the bot
        if(loopCount>maxLoopCount){
            end = true;
        }
    }
    actionPointer++;
    //after pushing the pointer, if reach end, stop the bot
    if(actionPointer == actions.size()){
        end = true;
    }
    return actions[actionPointer];
}

void Bot::reset(){
    actionPointer = 0;
    hited = false;
    end = compile();
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
