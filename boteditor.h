#ifndef BOTEDITOR_H
#define BOTEDITOR_H

#include <QObject>
#include "bot.h"

class BotEditor : public QObject
{
    Q_OBJECT
public:
    BotEditor();
    void setTarget(Bot*);
public slots:
    void addDo();
    void addUntilHit();
    void addForward();
    void addRight();
    void addLeft();
    void addNoAction();
signals:
    void updatePreviewer();
private:
    Bot* target;

};

#endif // BOTEDITOR_H
