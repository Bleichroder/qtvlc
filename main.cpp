#include "system.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vlcsystem sys;

    return a.exec();
}
