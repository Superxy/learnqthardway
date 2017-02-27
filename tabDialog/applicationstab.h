#ifndef APPLICATIONSTAB_H
#define APPLICATIONSTAB_H

#include <QWidget>
#include <QFileInfo>

class ApplicationsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationsTab(const QFileInfo &fileinfo, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // APPLICATIONSTAB_H
