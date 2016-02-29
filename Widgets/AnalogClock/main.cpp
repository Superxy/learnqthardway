#include <QApplication>
#include "analogclock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AnalogClock aclock;
    aclock.show();
    return a.exec();
}
