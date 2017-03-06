#include <QApplication>
#include <QTableView>
#include "mymodel.h"

/*
通过data()的消息日志发现，以Cell(0,0)为例：
系统自动调用data()
"row0,col0,role6"
"row0,col0,role7"
"row0,col0,role9"
"row0,col0,role10"
"row0,col0,role1"
"row0,col0,role0"
"row0,col0,role8"
role的值自动变化成6,7,9,10,1,0,8 一共被调用7次
switch()中没有处理的role (1,9)要返回QVariant()。
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTableView *myTable = new QTableView;
    MyModel myModel(0);

    myTable->setModel(&myModel);
    myTable->show();


    return app.exec();
}
