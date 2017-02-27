#include "tabdialog.h"
#include <generaltab.h>
#include <permissiontab.h>
#include <applicationstab.h>
#include <QFileInfo>
#include <QLayout>

TabDialog::TabDialog(const QString &fileName, QWidget *parent) : QDialog(parent)
{
    QFileInfo fileInfo(fileName);

    tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralTab(fileInfo), tr("General"));
    tabWidget->addTab(new PermissionTab(fileInfo), tr("Permission"));
    tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Application"));

    //创建两个button, OK 和 Cancel
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this,  SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Tab Dialog"));
}

TabDialog::~TabDialog()
{
    
}
