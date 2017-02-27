#ifndef PERMISSIONTAB_H
#define PERMISSIONTAB_H

#include <QWidget>
#include <QFileInfo>

class PermissionTab : public QWidget
{
    Q_OBJECT
public:
    explicit PermissionTab(const QFileInfo &fileinfo, QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PERMISSIONTAB_H
