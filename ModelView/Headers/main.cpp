#include <QApplication>
#include <QTableView>
#include "mymodel.h"

/*
    给表列起名字
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTableView tableView;
    MyModel myModel(0);

    tableView.setModel(&myModel);
    tableView.show();

    return app.exec();
}
