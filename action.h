#ifndef ACTION_H
#define ACTION_H
#include <QString>

class Action
{
public:
    Action();
    Action(QString name, int duration);
    Action(QString name, int duration, bool* condition);
private:
    QString name;
    int duration;

};

#endif // ACTION_H
