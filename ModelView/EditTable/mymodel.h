#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>

int const ROW = 2;
int const COL = 3;


class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    //bool QAbstractItemModel::setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole ) [virtual]
    //index表示行列，value表示单元格的值，Qt::EditRole这个值可以被编辑
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    //Qt::ItemFlags QAbstractItemModel::flags ( const QModelIndex & index ) const [virtual]
    //返回index单元格的flag
    /*
    This enum describes the properties of an item:
    Constant	Value	Description
    Qt::NoItemFlags	0	It does not have any properties set.
    Qt::ItemIsSelectable	1	It can be selected.
    Qt::ItemIsEditable	2	It can be edited.
    Qt::ItemIsDragEnabled	4	It can be dragged.
    Qt::ItemIsDropEnabled	8	It can be used as a drop target.
    Qt::ItemIsUserCheckable	16	It can be checked or unchecked by the user.
    Qt::ItemIsEnabled	32	The user can interact with the item.
    Qt::ItemIsTristate	64	The item is checkable with three separate states.
    */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    
signals:
    void editCompleted(const QString &);
private:
    QString m_gridData[ROW][COL];
    
};

#endif // MYMODEL_H
