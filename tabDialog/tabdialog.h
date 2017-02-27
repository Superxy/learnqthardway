#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>

class TabDialog : public QDialog
{
    Q_OBJECT
    
public:
    TabDialog(const QString &fileName, QWidget *parent = 0);
    ~TabDialog();
private:
    //QTabWidget:窗体切换类
    QTabWidget *tabWidget;
    //QDialogButtonBox:在layout中展示button，并且layout和当前的widget style一致
    QDialogButtonBox *buttonBox;
};

#endif // TABDIALOG_H
