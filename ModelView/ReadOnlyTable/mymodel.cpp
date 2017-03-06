#include "mymodel.h"

MyModel::MyModel(QObject *parent) :
    QAbstractTableModel (parent)
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
        QString data = tr("Row%1,Colunm%2").arg(index.row()+1).arg(index.column()+1);
        return data;
    }
    else
        return QVariant();
}
