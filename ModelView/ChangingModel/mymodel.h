#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QTimer>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QTimer *timer;
signals:
    
private slots:
    void timerHit();
};

#endif // MYMODEL_H
