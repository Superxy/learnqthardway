#include <QApplication>
#include <QTableView>
#include "mymodel.h"

/*
    这个小程序展示了Model的被动性，Model不知道什么时候被调用，什么内容需要。
    它只在View每次请求的时候，提供data()。
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTableView *qTableView = new QTableView;
    MyModel myModel(0);
    //setModel()
    //1.告诉qTableView多少行多少列需要展示
    //2.每个单元格需要展示什么内容,就是data（）返回值
    qTableView->setModel(&myModel);
    qTableView->show();

    return app.exec();
}


