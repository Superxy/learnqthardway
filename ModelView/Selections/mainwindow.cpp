#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QItemSelectionModel>
#include <QItemSelection>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeView = new QTreeView(this);
    setCentralWidget(treeView);
    standardModel = new QStandardItemModel(this);
    QStandardItem *rootNode = standardModel->invisibleRootItem();

    //defining a couple of items
    QStandardItem *americaItem = new QStandardItem("America");
    QStandardItem *mexicoItem =  new QStandardItem("Canada");
    QStandardItem *usaItem =     new QStandardItem("USA");
    QStandardItem *bostonItem =  new QStandardItem("Boston");
    QStandardItem *europeItem =  new QStandardItem("Europe");
    QStandardItem *italyItem =   new QStandardItem("Italy");
    QStandardItem *romeItem =    new QStandardItem("Rome");
    QStandardItem *veronaItem =  new QStandardItem("Verona");

    //building up the hierarchy
   rootNode->    appendRow(americaItem);
   rootNode->    appendRow(europeItem);
   americaItem-> appendRow(mexicoItem);
   americaItem-> appendRow(usaItem);
   usaItem->     appendRow(bostonItem);
   europeItem->  appendRow(italyItem);
   italyItem->   appendRow(romeItem);
   italyItem->   appendRow(veronaItem);

   treeView->setModel(standardModel);
   treeView->expandAll();

   QItemSelectionModel *selectModel = treeView->selectionModel();
   //每当选择改变时候。发射void QItemSelectionModel::selectionChanged [signal]
   connect(selectModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
           this, SLOT(selectionChanged(QItemSelection,QItemSelection)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection)
{
    //QItemSelectionModel * QAbstractItemView::selectionModel () const 返回当前的selection model.
    //获取当前的Index。
    const QModelIndex index = treeView->selectionModel()->currentIndex();
    //获取当前的text
    QString selectedText = index.data(Qt::DisplayRole).toString();
    //寻找当前hierarchy level
    int hierarchyLevel = 1;
    QModelIndex seekRoot = index;
    //QModelIndex() 构造函数生产的parent是无效的
    //QStandardItem *americaItem 的parent也是无效的
    QModelIndex parent = QModelIndex();
    while(seekRoot.parent() != parent)
    {
        seekRoot = seekRoot.parent();
        ++hierarchyLevel;
    }
    QString levelText = QString("%1,level%2").arg(selectedText).arg(hierarchyLevel);
    setWindowTitle(levelText);
}
