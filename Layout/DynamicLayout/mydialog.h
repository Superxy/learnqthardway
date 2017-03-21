#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QQueue>

class QComboBox;
class QDialogButtonBox;
class QGridLayout;
class QGroupBox;
class QLabel;
class QPushButton;

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();
    
private:
    Ui::MyDialog *ui;
    void createRotableGroupBox();
    void createOptionsGroupBox();
    void createButtonBox();

    QGroupBox *rotableGroupBox;
    QQueue<QWidget *> rotableWidgets;

    QGroupBox *optionsGroupBox;
    QLabel *buttonsOrientationLabel;
    QComboBox *buttonsOrientationComboBox;

    QDialogButtonBox *buttonBox;
    QPushButton *closeButton;
    QPushButton *helpButton;
    QPushButton *rotateWidgetsButton;

    QGridLayout *mainLayout;
    QGridLayout *rotableLayout;
    QGridLayout *optionsLayout;

private slots:
    void buttonsOrientationChanged(int index);
    void rotateWidgets();
    void help();



};

#endif // MYDIALOG_H
