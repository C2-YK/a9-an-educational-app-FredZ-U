#include "connecter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connecter c;
    c.show();
    return a.exec();
}
