#ifndef BOTEDITORRENDER_H
#define BOTEDITORRENDER_H

#include <QObject>
#include <QList>
#include <QString>
#include "bot.h"

class BotEditorRender : public QObject
{
    Q_OBJECT
public:
    BotEditorRender();
    void setBot(Bot*);
    void updateViewer();
signals:
    void updateActions(QList<QString> actions);
private:
    Bot* target;
};

#endif // BOTEDITORRENDER_H
