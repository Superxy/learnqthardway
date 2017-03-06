#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTreeView;
class QStandardItemModel;
class QItemSelection;

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
    QStandardItemModel *standardModel;
private slots:
    void selectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection);
};

#endif // MAINWINDOW_H
