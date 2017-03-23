#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //application是qrc，也就是qt资源文件，用来保存图片和文字等
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    //应用程序经常有这样的要求：要求它能记住它的settings，比如窗口大小，位置，一些别的设置,Qsettings来实现
    //Qsettings对象需要2个参数，组织名称和应用程序名称
    app.setOrganizationName("Trolltech");
    app.setApplicationName("Application Example");
    MainWindow w;
    w.show();
    
    return app.exec();
}
