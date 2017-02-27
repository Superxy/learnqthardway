#include "applicationstab.h"

#include <QLabel>
#include <QListWidget>
#include <QCheckBox>
#include <QLayout>

ApplicationsTab::ApplicationsTab(const QFileInfo &fileInfo, QWidget *parent) :
    QWidget(parent)
{
    QLabel *topLabel = new QLabel(tr("Open With:"));
    //QListWidget：provides an item-based list widget
    QListWidget *applicationsListBox = new QListWidget;
    QStringList applications;

    for(int i=0; i<=30; i++)
        applications.append(tr("Applications %1").arg(i));

    applicationsListBox->insertItems(0, applications);

    QCheckBox *alwaysCheckBox;

    if (fileInfo.suffix().isEmpty())
           alwaysCheckBox = new QCheckBox(tr("Always use this application to open this type of file"));
       else
           alwaysCheckBox = new QCheckBox(tr("Always use this application to open files with the extension '%1'").arg(fileInfo.suffix()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(applicationsListBox);
    layout->addWidget(alwaysCheckBox);
    setLayout(layout);

}
