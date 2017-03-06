#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    treeView = new QTreeView(this);
    setCentralWidget(treeView);

    standardItemModel = new QStandardItemModel(this);

    QList<QStandardItem *> preparedRow = prepareRow("First", "Second", "Third");
    //返回一个不可见的root Item
    //这个不可见的root Item通过QStandardItem API来使用
    QStandardItem *rootItem = standardItemModel->invisibleRootItem();
    //添加一行
    rootItem->appendRow(preparedRow);

    QList<QStandardItem *> secondRow = prepareRow("111", "222", "333");
    //T & QList::first ()
    //返回List中的第一个Item
    //第一个Item再添加一行。
    preparedRow.first()->appendRow(secondRow);

    treeView->setModel(standardItemModel);
    //所有的树都显示出来
    treeView->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QList<QStandardItem *> MainWindow::prepareRow(const QString &first, const QString &second, const QString &third)
{
   QList<QStandardItem *> rowItems;
   //QList<T> & QList::operator<< ( const T & value )
   //QList类的一个重载操作符
   rowItems << new QStandardItem(first);
   rowItems << new QStandardItem(second);
   rowItems << new QStandardItem(third);

   return rowItems;
}

