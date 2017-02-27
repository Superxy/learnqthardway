#include "tabdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString fileName;

    fileName = "G://others//tabDialog//main.cpp";

    TabDialog tabDialog(fileName);
    tabDialog.show();
    
    return a.exec();
}
