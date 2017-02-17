#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QLayout>

class QLineEdit;
class QLabel;
class QPushButton;
class QCheckBox;

class findDialog : public QDialog
{
    Q_OBJECT
public:
    findDialog(QWidget *parent = 0);
signals:
    // Qt::CaseSensitive 比较字符串时区分大小写， Qt::CaseInSensitive 不区分大小写
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
private slots:
    void findClicked();
    void enableFindButton(const QString &text);
private:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *findButton;
    QPushButton *closeButton;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
};

#endif // FINDDIALOG_H
