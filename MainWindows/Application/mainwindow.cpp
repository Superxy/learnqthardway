#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),this, SLOT(documentWasModified()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if(maybeSave()) {
        writeSettings();
        //void QEvent::accept ()
        //事件对象设置 accept flag
        //表示事件接收器希望处理这个事件
        event->accept();
    }
    else {
        //清除accept flag
        //表示事件接收器忽略这个事件
        event->ignore();
    }

}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    //官方的快捷键设置 QKeySequence::New ctr+N
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                        "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                          "clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                           "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
                 cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
                 copyAct, SLOT(setEnabled(bool)));



}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}

void MainWindow::readSettings()
{
    //初始化QSettings对象
    QSettings settings("Trolltech", "Application Example");
    //QVariant QSettings::value ( const QString & key, const QVariant & defaultValue = QVariant() ) const
    //获得 pos 和 size的值，如果是第一次打开应用程序 pos(200,200) size(400,400)
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();

    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    //初始化QSettings对象
    QSettings settings("Trolltech", "Application Example");
    //关闭应用程序时，获得当前的位置和大小
    //并把当前的配置存入“pos” “size”中
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


bool MainWindow::maybeSave()
{
    //QTextDocument * QPlainTextEdit::document () const 返回QTextDocument指针
    if(textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
    //QMessageBox static function
    //StandardButton warning(QWidget *parent,const QString &title, const QString &text, StandardButtons buttons = Ok)
        ret = QMessageBox::warning(this, tr("application"), tr("The document has been modified.\n"
                                   "Do you want to save?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(ret == QMessageBox::Save)
            return save();
        else if(ret == QMessageBox::Cancel)
            return false;
    }

    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
             QMessageBox::warning(this, tr("Application"),
                                  tr("Cannot read file %1:\n%2.")
                                  .arg(fileName)
                                  .arg(file.errorString()));
             return;
    }

    QTextStream in(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    textEdit->setPlainText(in.readAll());
    file.close();

    QApplication::restoreOverrideCursor();


    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    //如果新建的文件不能写入
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                                   tr("Cannot write file %1:\n%2.")
                                    .arg(fileName)
                                    .arg(file.errorString()));

        return false;
    }

    //QTextStream提供特别方便的读写文件功能
    QTextStream out(&file);
    //将当前的游标变成等待游标
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //将textEdit中的文本写入
    out << textEdit->toPlainText();
    //恢复游标
    QApplication::restoreOverrideCursor();
    //对应open()
    file.close();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File Saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowTitle(strippedName(curFile));
    textEdit->document()->setModified(false);

    //QWidget::windowModified : bool
    //用来表明QWidget中的文本是否有unsaved changes
    setWindowModified(false);

    QString showName = curFile;
    if(showName.isEmpty())
        showName = "untitled.txt";
    //保存文件的路径
    setWindowFilePath(showName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    //把文件名中的路径去除
    return QFileInfo(fullFileName).fileName();
}


/*
    6个槽
*/

void MainWindow::newFile()
{
    //如果如果文件的改动被保存
    if(maybeSave()) {
        //清空当前文件
        textEdit->clear();
        //打开新的文件，空文件
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    //如果文件的改动被保存
    if(maybeSave()) {
        //打开新文件
        QString fileName = QFileDialog::getOpenFileName(this);
        //新文件不是空文件，则载入新文件
        if(!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

bool MainWindow::save()
{
    if(curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);
}

bool MainWindow::saveAs()
{
    //打开QFileDialog对话框，获取文件名
    QString fileName = QFileDialog::getSaveFileName(this);
    if(fileName.isEmpty())
        return false;
    else
        return saveFile(fileName);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Application"),
                 tr("The <b>Application</b> example demonstrates how to "
                    "write modern GUI applications using Qt, with a menu bar, "
                    "toolbars, and a status bar."));
}

void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}


