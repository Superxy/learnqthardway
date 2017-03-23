#include "extenddialog.h"
#include "ui_extenddialog.h"
#include <QLayout>

extendDialog::extendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::extendDialog)
{
    ui->setupUi(this);
    /*
    由于QDialog类的窗口默认只有“这是什么”和“关闭”按钮
    为了去掉“这是什么”按钮，需要更改WindowFlags
    */
    Qt::WindowFlags flags=Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);

    ui->secondaryGroupBox->hide();
    ui->tertiaryGroupBox->hide();
    /*
    隐藏了secondaryGroupBox 和 tertiaryGroupBox之后
    把窗体布局的属性SizeConstraint 设置成QLayout::SetFixedSize
    这样布局管理器就会重新来定义窗体的大小
    */
    /*
    如果不在qt designer中对整个的dialog栅格布局，layout()的值就是0，引用空指针就会出现 SIGSEGV
    */

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setColumnRange('A','Z');

}

extendDialog::~extendDialog()
{
    delete ui;
}


void extendDialog::setColumnRange(QChar first, QChar last)
{
    ui->primaryColumnCombo->clear();
    ui->secondaryColumnCombo->clear();
    ui->tertiaryColumnCombo->clear();

    ui->secondaryColumnCombo->addItem(tr("None"));
    ui->tertiaryColumnCombo->addItem(tr("None"));
    /*
    secondaryColumnCombo和tertiaryColumnCombo 比primaryColumnCombo 多一行“None”
    “None” 比一个字母 ‘A’ 显得宽些
    为了避免这种不一致，把primaryColumnCombo的最小尺寸设置成secondaryColumnCombo的理想尺寸
    */

    ui->primaryColumnCombo->setMinimumSize(ui->secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while(ch != last)
    {
        ui->primaryColumnCombo->addItem(QString(ch));
        ui->secondaryColumnCombo->addItem(QString(ch));
        ui->tertiaryColumnCombo->addItem(QString(ch));
        ch = ch.unicode()+1;
    }

}

