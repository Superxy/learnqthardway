#include "mymodel.h"
#include <QTime>
#include <QModelIndex>

MyModel::MyModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    timer = new QTimer(this);
    //设置定时器的timeout
    timer->setInterval(1000);
    //如果SingleShot为ture。就只发射一次timeout信号。
    //如果SingleShot为false。就无限发射timeout信号。
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
    //开始定时器，计时。
    timer->start();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    return 2;
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if(role == Qt::DisplayRole)
    {
        if(row == 0 && col == 0)
        {
            return QTime::currentTime().toString();
        }
        if(row == 0 && col == 1)
        {
            return QTime::currentTime().toString();
        }
    }

    return QVariant();
}

void MyModel::timerHit()
{
    //根据行和列创建QModelIndex
    QModelIndex index1 = createIndex(0, 0);
    QModelIndex index2 = createIndex(0, 1);
    //index1 index2 之间的区域全部发射dataChanged信号
    emit dataChanged(index1, index2);
}
