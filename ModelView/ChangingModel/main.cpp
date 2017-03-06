#include <QApplication>
#include <QTableView>
#include "mymodel.h"

/*
    目前我们的表只是readonly，现在表的一个单元格的内容将无限的改变，因为展示的是当前的时间
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*
    使用QTableView *tableView = new QTableView 就会出现错误
    空的Qt项目，tableView没有父类，指针不会自动删除。
    */
    QTableView tableView;
    MyModel myModel(0);

    tableView.setModel(&myModel);
    tableView.show();

    return app.exec();
}
