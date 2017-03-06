#include "mymodel.h"

MyModel::MyModel(QObject *parent) :
    QAbstractTableModel(parent)
{
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
    if(role == Qt::DisplayRole)
    {
        return QString("row%1,col%2").arg(index.row()).arg(index.column());
    }
    return QVariant();
}

//section表示是多少列 从0开始
//Qt::Orientation 表示对象的指向。一列一列的表头是横向的
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section) {
            case 0:
                return QString("First");
                break;
            case 1:
                return QString("Second");
                break;
            case 2:
                return QString("Third");
                break;
            default:
                break;
            }
        }
    }

    return QVariant();
}
