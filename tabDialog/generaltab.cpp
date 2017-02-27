#include "generaltab.h"
#include <QLabel>
#include <QLineEdit>
#include <QDateTime>
#include <QLayout>

GeneralTab::GeneralTab(const QFileInfo &fileinfo,QWidget *parent) :
    QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    // QFileInfo fi("/tmp/archive.tar.gz");
    //QString name = fi.fileName();                // name = "archive.tar.gz"
    QLineEdit *fileNameLineEdit = new QLineEdit(fileinfo.fileName());

    QLabel *pathLabel = new QLabel(tr("Path:"));
    // QFileInfo fi("c:/temp/foo"); => fi.absoluteFilePath() => "C:/temp/foo"
    QLabel *pathValueLabel = new QLabel(fileinfo.absoluteFilePath());
    //设置整个框架的style，从 QFrame::Shape 和 QFrame::Shadow两个枚举中取值
    //QFrame::Panel 调色板来决定内容凸起或者凹下去
    //QFrame::Sunken 凹下去
    pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *sizeLabel = new QLabel(tr("Size:"));
    //size()函数返回byte  size表示有多少K字节
    qlonglong size = fileinfo.size() / 1024;
    //Qstring::arg()
    QLabel *sizeValueLabel = new QLabel(tr("%1 K").arg(size));
    sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *lastReadLabel = new QLabel(tr("Last Read:"));
    //lastRead() 返回QDateTime
    QLabel *lastReadValueLabel = new QLabel(fileinfo.lastRead().toString());
    lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *lastModLabel = new QLabel(tr("Last Modify:"));
    //lastModified() 返回QDateTime
    QLabel *lastModValueLabel = new QLabel(fileinfo.lastModified().toString());
    lastModValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameLineEdit);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(pathValueLabel);
    mainLayout->addWidget(sizeLabel);
    mainLayout->addWidget(sizeValueLabel);
    mainLayout->addWidget(lastReadLabel);
    mainLayout->addWidget(lastReadValueLabel);
    mainLayout->addWidget(lastModLabel);
    mainLayout->addWidget(lastModValueLabel);
    mainLayout->addStretch(1);

    setLayout(mainLayout);



}
