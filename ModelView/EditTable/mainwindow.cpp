#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAbstractItemModel>
#include "mymodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableView = new QTableView(this);
    setCentralWidget(tableView);
    // 多态：父类指针指向子类指针
    // 调用时候使用子类重写的方法
    QAbstractTableModel *myModel = new MyModel(this);

    tableView->setModel(myModel);
//    tableView->setMinimumWidth(400);
//    tableView->setMinimumHeight(500);
    tableView->show();

    connect(myModel, SIGNAL(editCompleted(const QString &)), this, SLOT(setWindowTitle(const QString &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showWindowTitle(const QString &title)
{
    setWindowTitle(title);
}
