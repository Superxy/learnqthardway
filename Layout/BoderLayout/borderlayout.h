#ifndef BORDERLAYOUT_H
#define BORDERLAYOUT_H

#include <QLayout>
#include <QRect>

class BorderLayout : public QLayout
{
    Q_OBJECT
public:
    enum Position { West, North, South, East, Center };

    explicit BorderLayout(QWidget *parent, int margin = 0, int spacing = -1);
    BorderLayout(int spacing = -1);
    ~BorderLayout();

    //4个纯虚函数 必须实现
    void addItem(QLayoutItem *item);
    int count() const;
    QLayoutItem * itemAt(int index) const;
    QLayoutItem * takeAt(int index);

    void addWidget(QWidget *w, Position position);
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    void add(QLayoutItem *item, Position position);

private:
    struct ItemWrapper
   {
       ItemWrapper(QLayoutItem *i, Position p) {
       item = i;
       position = p;
       }

       QLayoutItem *item;
       Position position;
   };

   enum SizeType { MinimumSize, SizeHint };
   QSize calculateSize(SizeType sizeType) const;

   QList<ItemWrapper *> list;
    
};

#endif // BORDERLAYOUT_H
