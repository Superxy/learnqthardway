#include "finddialog.h"


findDialog::findDialog(QWidget *parent) : QDialog(parent)
{
    // QObject::tr()处理的字符串可以用工具提取翻译成其他语言，国际化使用。
    // &w --> 快捷键 Alt+w
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    //QLabel::setBuddy() 当按快捷键时候，光标移动到它的Buddy上。
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    //QPushButton::setDefault()
    //决定在dialog中按enter键时发生什么，如果是true，按钮将被pressed，当按下enter键时。
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    // 信号和槽中的函数都是只有参数类型。没有参数名称，因为SIGNAL和SLOT宏将把参数转化成字符串
    //connect(lineEdit, SIGNAL(textChanged(const QString &str)), this, SLOT(enableFindButton(const QString &str)));错误
    //connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));正确
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));

    QHBoxLayout *leftTopLayout = new QHBoxLayout;
    leftTopLayout->addWidget(label);
    leftTopLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(leftTopLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Find"));
    //virtual QSize	sizeHint() const  返回推荐的widget尺寸
    setFixedHeight(sizeHint().height());

}

void findDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if(backwardCheckBox->isChecked())
        emit findPrevious(text, cs);
    else
        emit findNext(text, cs);
}

void findDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}
