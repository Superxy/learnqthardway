#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "borderlayout.h"

#include <QLabel>
#include <QTextBrowser>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextBrowser *centralWidget = new QTextBrowser;
    centralWidget->setPlainText(tr("Central Widget"));

    BorderLayout *borderLayout = new BorderLayout;

    borderLayout->addWidget(centralWidget, BorderLayout::Center);
    borderLayout->addWidget(createLabel("North"), BorderLayout::North);
    borderLayout->addWidget(createLabel("West"), BorderLayout::West);
    borderLayout->addWidget(createLabel("East 1"), BorderLayout::East);
    borderLayout->addWidget(createLabel("East 2") , BorderLayout::East);
    borderLayout->addWidget(createLabel("South"), BorderLayout::South);



    //直接使用setLayout(borderLayout) 会产生错误 "MainWindow", which already has a layout
    //因为QMainWindow 本来就有一个Layout包含 centralWidget，menuBar， toolBar
    //所以只能在centralWidget上布局
    ui->centralWidget->setLayout(borderLayout);

    setWindowTitle(tr("Border Layout"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


QLabel *MainWindow::createLabel(const QString &label)
{
    QLabel *newLabel = new QLabel(label);
    /*
    enum QFrame::Shape  这个枚举常量决定Frame的形状
    QFrame::Box	0x0001	QFrame draws a box around its contents
    QFrame::Panel	0x0002	QFrame draws a panel to make the contents appear raised or sunken
    */
    /*
    enum QFrame::Shadow 如何用3D效果展示Frame
    QFrame::Plain	0x0010	没有任何3d效果
    QFrame::Raised	0x0020	凸出来
    QFrame::Sunken  0x0030  凹进去
    */
    newLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    return newLabel;
}
