#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QWidget>
#include <QFileInfo>

class GeneralTab : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralTab(const QFileInfo &fileinfo, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GENERALTAB_H
