#ifndef BOTEDITOR_H
#define BOTEDITOR_H

#include <QObject>
#include "bot.h"

class BotEditor : public QObject
{
    Q_OBJECT
public:
    BotEditor();
    void setBot(Bot*);
public slots:
    void addDo();
    void addUntilHit();
    void addForward();
    void addRight();
    void addLeft();
    void addNoAction();
    void removeLastAction();
    void removeAllActions();
signals:
    void updatePreviewer();
private:
    Bot* target;

};

#endif // BOTEDITOR_H
