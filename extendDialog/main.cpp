#include "extenddialog.h"
#include <QApplication>

/*
以往的对话框都不能改变形状，有的情况下需要可以改变形状的对话框。
有一般有两种对话框： 扩展对话框（extension dialog） 多页对话框（multi-page dialog）
这两种对话框用纯粹的代码或者Qt设计师都可以实现
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    extendDialog w;
    w.show();
    
    return a.exec();
}
