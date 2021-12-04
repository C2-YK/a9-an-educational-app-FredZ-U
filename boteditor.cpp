#include "boteditor.h"

BotEditor::BotEditor()
{

}

void BotEditor::setBot(Bot * b){
    target = b;
}

void BotEditor::addDo(){
    target->addAction(target->Do);
}

void BotEditor::addUntilHit(){
    target->addAction(target->UntilHit);
}

void BotEditor::addForward(){
    target->addAction(target->Forward);
}

void BotEditor::addRight(){
    target->addAction(target->Right);
}

void BotEditor::addLeft(){
    target->addAction(target->Left);
}

void BotEditor::addNoAction(){
    target->addAction(target->noAction);
}

void BotEditor::removeLastAction(){
    target->removeLastAction();
}

void BotEditor::clearActions(){
    while(target->removeLastAction()){}
}
