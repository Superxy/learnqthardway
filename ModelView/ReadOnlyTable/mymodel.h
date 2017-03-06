#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>

class MyModel : public QAbstractTableModel 
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = 0);
    //QModelIndex::QModelIndex () 创建一个空的ModelIndex,用空的ModelIndex去告知Model中行列是无效的
    //int QAbstractItemModel::rowCount(const QModelIndex & parent = QModelIndex())const [pure virtual]
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    //int QAbstractItemModel::columnCount (const QModelIndex & parent = QModelIndex())const [pure virtual]
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    //QVariant QAbstractItemModel::data (const QModelIndex & index, int role = Qt::DisplayRole )const [pure virtual]
    //行和列储存在index中
    //enum Qt::ItemDataRole
    //role通过View使用，告诉Model那种类型的数据它需要。
    //Qt::DisplayRole	0	The key data to be rendered in the form of text.(QString)
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    
signals:
    
public slots:
    
};

#endif // MYMODEL_H
