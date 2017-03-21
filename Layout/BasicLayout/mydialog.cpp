#include "mydialog.h"
#include "ui_mydialog.h"

#include <QAction>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    createMenu();
    createHorizontalGroupBox();
    createGridGroupBox();
    createFormGroupBox();

    bigEditor = new QTextEdit(tr("Big Editor"));
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);


    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(gridGroupBox);
    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(bigEditor);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    setWindowTitle(tr("Basic Layout"));

}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::createMenu()
{
    //创建菜单栏
    menuBar = new QMenuBar;
    //创建菜单
    fileMenu = new QMenu(tr("&File"), this);
    //生产菜单Action
    exitAction = fileMenu->addAction(tr("E&xit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    //将菜单添加到菜单栏
    menuBar->addMenu(fileMenu);
}

void MyDialog::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Horizontal Layout"));

    QHBoxLayout *groupLayout = new QHBoxLayout;
    for(int i=0; i<NumButtons; i++) {
        buttons[i] = new QPushButton(tr("Button %1").arg(i+1));
        groupLayout->addWidget(buttons[i]);
    }

    horizontalGroupBox->setLayout(groupLayout);
}

void MyDialog::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Grid Layout"));

    QGridLayout *gridLayout = new QGridLayout;

    for(int i=0; i<NumGridRows; i++) {
        labels[i] = new QLabel(tr("Label %1").arg(i+1));
        lineEdits[i] = new QLineEdit;
        //label 放在第1~3行 0列
        gridLayout->addWidget(labels[i],i+1,0);
        //lineEdit 放在第1~3行  1列
        gridLayout->addWidget(lineEdits[i],i+1,1);
        // 第0行 空缺
    }

    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the grid layout"));
    //smallEditor 放在第0行2列  跨度4行1列
    //因此smallEditor下端和labels[2] lineEdits[2] 平齐
    gridLayout->addWidget(smallEditor,0,2,4,1);

    //将第1列拉伸  lineEdits 比 labels 横向长大约10倍
    gridLayout->setColumnStretch(1,10);
    //将第2列拉伸  smallEditor 比 lineEdits 横向长大约2倍
    gridLayout->setColumnStretch(2,20);

    gridGroupBox->setLayout(gridLayout);
}

void MyDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form Layout"));
    QFormLayout *formLayout = new QFormLayout;
    //void	addRow ( QWidget * label, QWidget * field )
    formLayout->addRow(new QLabel(tr("Line 1")), new QLineEdit);
    formLayout->addRow(new QLabel(tr("Line 2,Long Text")), new QComboBox);
    formLayout->addRow(new QLabel(tr("Line 3")), new QSpinBox);



    formGroupBox->setLayout(formLayout);
}
