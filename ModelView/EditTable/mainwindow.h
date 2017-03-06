#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QTableView *tableView;
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

public slots:
    void showWindowTitle(const QString &title);
};

#endif // MAINWINDOW_H
