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
    void deleteAction(int index);
    void clearActions();
signals:
    void updatePreviewer();
    void compiled(bool success);
private:
    Bot* target;

};

#endif // BOTEDITOR_H
