#include "finddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    findDialog *dialog = new findDialog;
    dialog->show();
    return a.exec();
}
