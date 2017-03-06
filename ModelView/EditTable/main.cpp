#include "mainwindow.h"
#include <QApplication>

/*
1.Qt::Itemflags flags(const QModelIndex &index)
   return Qt::ItemIsEditable | QAbstractItemModel::flags(index)
   返回单元格的flags。该flags表示此单元格是可以编辑的
2.编辑单元格调用 setData 方法
  该方法把数据放入 m_gridData[ROW][COL]中。
  并把m_gridData[ROW][COL] 中所有的数据存入result中，作为MainWindow的标题
3.tableView调用data方法，把m_gridData[ROW][COL]内容显示到单元格中
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
