#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QTreeView *treeView;
    /*
      QStandardItemModel类提供一个通用的Model来储存数据。
      QStandardItemModel能作为Qt数据类的仓库。例如 Model/View Classes那些 Qt's model/view framework.
      QStandardItemModel必须被QStandardItem 填充。
    */
    QStandardItemModel *standardItemModel;
    QList<QStandardItem *> prepareRow(const QString &first, const QString &second, const QString &third);
};

#endif // MAINWINDOW_H
