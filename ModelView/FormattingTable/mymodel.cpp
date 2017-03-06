#include "mymodel.h"
#include <QDebug>
#include <QFont>
#include <QBrush>

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
    int row = index.row();
    int column = index.column();
    //每当调用data()生成消息日志
    qDebug() << QString("row%1,col%2,role%3").arg(row).arg(column).arg(role);

    switch (role) {
    //Qt::DisplayRole 0	通过QString传递数据给View
    case Qt::DisplayRole:
        {
        if(row == 0 && column == 1)
            return QString("<--left");
        if(row == 1 && column == 1)
            return QString("right-->");

        return
                QString("Row%1,Col%2").arg(row+1).arg(column+1);
        }
        break;
    //Qt::FontRole	6   设置字体
    case Qt::FontRole:
        {
            //cel(0,0)变成粗体
            if(row == 0 && column == 0)
            {
                QFont boldFront;
                boldFront.setBold(true);
                return boldFront;
            }

        }
        break;
    //Qt::BackgroundRole 8 QBrush设置背景颜色
    case Qt::BackgroundRole:
        {
            if(row == 1 && column == 2)
            {
                QBrush redBrush(Qt::red);
                return redBrush;
            }
        }
        break;
    //Qt::TextAlignmentRole	7  设置TextAlign
    case Qt::TextAlignmentRole:
        {
            if(row == 1 && column == 1)
                return Qt::AlignRight + Qt::AlignVCenter;
        }
        break;
    //Qt::CheckStateRole	10	CheckState
    case Qt::CheckStateRole:
        {
            if (row == 1 && column == 0) //add a checkbox to cell(1,0)
            {
                return Qt::Checked;
            }
        }
        break;
    default:
        break;
    }

    return QVariant();
}
