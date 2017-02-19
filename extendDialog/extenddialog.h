#ifndef EXTENDDIALOG_H
#define EXTENDDIALOG_H

#include <QDialog>

namespace Ui {
class extendDialog;
}

class extendDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit extendDialog(QWidget *parent = 0);
    ~extendDialog();
    void setColumnRange(QChar first, QChar last);
    
private:
    Ui::extendDialog *ui;
};

#endif // EXTENDDIALOG_H
