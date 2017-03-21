#include "mydialog.h"
#include "ui_mydialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QProgressBar>
#include <QDial>
#include <QSlider>
#include <QMessageBox>


MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);


    createRotableGroupBox();
    createOptionsGroupBox();
    createButtonBox();

    mainLayout = new QGridLayout;
    mainLayout->addWidget(rotableGroupBox, 0, 0);
    mainLayout->addWidget(optionsGroupBox, 1, 0);
    mainLayout->addWidget(buttonBox, 2, 0);
    setLayout(mainLayout);

    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

    setWindowTitle(tr("Dynamic Layouts"));
}

MyDialog::~MyDialog()
{
    delete ui;
}


void MyDialog::createButtonBox()
{
    buttonBox = new QDialogButtonBox;

    //QPushButton *	addButton ( StandardButton button )
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);
    helpButton = buttonBox->addButton(QDialogButtonBox::Help);

    //QPushButton *	addButton ( const QString & text, ButtonRole role )
    //enum QDialogButtonBox::ButtonRole 枚举变量用来描述buttonBox中的button
    //QDialogButtonBox::ActionRole 点击这个button，对话框中的元素可以改变
    rotateWidgetsButton = buttonBox->addButton(tr("Rotate &Widgets"), QDialogButtonBox::ActionRole);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(helpButton, SIGNAL(clicked()), this, SLOT(help()));
    connect(rotateWidgetsButton, SIGNAL(clicked()), this, SLOT(rotateWidgets()));
}

void MyDialog::createOptionsGroupBox()
{
    optionsGroupBox = new QGroupBox(tr("Options"));

    buttonsOrientationLabel = new QLabel(tr("Orientation of buttons:"));
    buttonsOrientationComboBox = new QComboBox;

    //void QComboBox::addItem ( const QString & text, const QVariant & userData = QVariant() )
    //buttonsOrientationComboBox->itemText() 获得Text
    //buttonsOrientationComboBox->itemData() 获得ItemData
    buttonsOrientationComboBox->addItem(tr("Horizontal"), Qt::Horizontal);
    buttonsOrientationComboBox->addItem(tr("Vertical"), Qt::Vertical);


    //当前comboBox选择改变，触发buttonsOrientationChanged(int) 槽
    connect(buttonsOrientationComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(buttonsOrientationChanged(int)));

    optionsLayout = new QGridLayout;
    optionsLayout->addWidget(buttonsOrientationLabel, 0, 0);
    optionsLayout->addWidget(buttonsOrientationComboBox, 0, 1);
    optionsLayout->setColumnStretch(2, 1);
    optionsGroupBox->setLayout(optionsLayout);
}

void MyDialog::createRotableGroupBox()
{
    rotableGroupBox = new QGroupBox(tr("Rotable Widgets"));

    rotableWidgets.enqueue(new QSpinBox);
    rotableWidgets.enqueue(new QSlider);
    rotableWidgets.enqueue(new QDial);
    rotableWidgets.enqueue(new QProgressBar);

    int n = rotableWidgets.count();
    //队列中前一个QWidget *值改变，后一个QWidget *值也改变
    for (int i = 0; i < n; ++i) {
           connect(rotableWidgets[i], SIGNAL(valueChanged(int)),
                   rotableWidgets[(i + 1) % n], SLOT(setValue(int)));
    }

    rotableLayout = new QGridLayout;
    rotableGroupBox->setLayout(rotableLayout);

    rotateWidgets();
}

void MyDialog::help()
{
    QMessageBox::information(this, tr("Dynamic Layouts Help"), tr("This example shows how to change layouts"
                                                                  " dynamically"));
}

void MyDialog::rotateWidgets()
{
    //判断Widget个数是否是2的倍数
    Q_ASSERT(rotableWidgets.count() % 2 == 0);

    //首先把rotableWidgets中所有的Widget从rotableLayout中删除
    foreach (QWidget *widget, rotableWidgets)
        rotableLayout->removeWidget(widget);

    //初始顺序 QSpinBox QSlider QDial QProgressBar
    //dequeue() 删除 QSpinBox
    //enqueue() 添加 QSpinBox
    //顺序： QSlider QDial QProgressBar QSpinBox
    rotableWidgets.enqueue(rotableWidgets.dequeue());

    const int n = rotableWidgets.count(); // n = 4
    //按 QSlider QDial QProgressBar QSpinBox 的顺序
    // i = 0
    // addWidget(rotableWidgets[3]=QSpinBox,0,0)
    // addWidget(rotableWidgets[0]=QSlider,1,0)
    // i = 1
    // addWidget(rotableWidgets[2]=QProgressBar,0,1)
    // addWidget(rotableWidgets[1]=QDial,1,1)
    for (int i = 0; i < n / 2; ++i) {
        rotableLayout->addWidget(rotableWidgets[n - i - 1], 0, i);
        rotableLayout->addWidget(rotableWidgets[i], 1, i);
    }
}

//改变buttonBox的布局
void MyDialog::buttonsOrientationChanged(int index)
{
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    setMinimumSize(0, 0);

    //从buttonsOrientationComboBox获得orientation
    Qt::Orientation orientation = Qt::Orientation(
            buttonsOrientationComboBox->itemData(index).toInt());

    if (orientation == buttonBox->orientation())
        return;

    //删除buttonBox
    mainLayout->removeWidget(buttonBox);

    int spacing = mainLayout->spacing(); //6

    //buttonBox->sizeHint() (254, 23)
    QSize oldSizeHint = buttonBox->sizeHint() + QSize(spacing, spacing);//(260,29)
    //重新设置orientation
    buttonBox->setOrientation(orientation);
    //buttonBox->sizeHint() (92,81)
    QSize newSizeHint = buttonBox->sizeHint() + QSize(spacing, spacing);//(98,87)

    if (orientation == Qt::Horizontal) {
        mainLayout->addWidget(buttonBox, 2, 0);
        //oldSizeHint表示右边的
        //newSizeHint表示下面的
        //原来的宽度减少,新的高度增加
        resize(size() + QSize(-oldSizeHint.width(), newSizeHint.height()));
    } else {
        mainLayout->addWidget(buttonBox, 0, 3, 2, 1);
       //size()返回值(400,300) 这个值是包括buttonBox的
       //现在要将buttonBox从下面移动到右边
       //高度要减少 -oldSizeHint.height()
       //宽度要增加 newSizeHint.width()
        resize(size() + QSize(newSizeHint.width(), -oldSizeHint.height()));
    }

    mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
}
