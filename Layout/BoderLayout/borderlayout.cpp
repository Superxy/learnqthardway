#include "borderlayout.h"

BorderLayout::BorderLayout(QWidget *parent, int margin, int spacing) :
    QLayout(parent)
{
    //Layout的边距
    setMargin(margin);
    //在Layout中控件之间的距离
    setSpacing(spacing);
}

BorderLayout::BorderLayout(int spacing)
{
    setSpacing(spacing);
}

//删除Layout中所有Item
BorderLayout::~BorderLayout()
{
    //Layout中所有的LayoutItem从0开始编号，删除一个Item，其他Item重新开始编号
    //如果Layout中没有Item,takeAt函数什么都不做，返回0
    //这个While循环用来删除Layout中所有LayoutItem
    QLayoutItem *child;
    while((child = takeAt(0)) != 0)
        delete child;

}

void BorderLayout::addItem(QLayoutItem *item)
{
    add(item, West);
}

//QWidgetItem  构造函数QWidgetItem ( QWidget * widget )
//QWidgetItem 继承自 QLayoutItem.
void BorderLayout::addWidget(QWidget *w, Position position)
{
    add(new QWidgetItem(w), position);
}

void BorderLayout::add(QLayoutItem *item, Position position)
{
    list.append(new ItemWrapper(item, position));
}

Qt::Orientations BorderLayout::expandingDirections() const
{
    return Qt::Horizontal | Qt::Vertical;
}


//如果Layout根据Width产生Height，返回ture，否则返回false
bool BorderLayout::hasHeightForWidth() const
{
    return false;
}

int BorderLayout::count() const
{
    //返回LayoutItem的个数
    return list.size();
}

QLayoutItem *BorderLayout::itemAt(int index) const
{
    //如果wrapper存在，返回wrapper->item
    ItemWrapper *wrapper = list.value(index);
    if(wrapper)
        return wrapper->item;
    else
        return 0;

}

//T QList::takeAt(index) 删除index所在的Item，并返回T
QLayoutItem *BorderLayout::takeAt(int index)
{
    if(index >= 0 && index < list.size())
    {
        ItemWrapper *layoutStruct = list.takeAt(index);
        return layoutStruct->item;
    }
    else
        return 0;
}

//返回LayoutminimumSize
QSize BorderLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

//返回Layout的sizeHint
QSize BorderLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

//计算出minimumSize和sizeHint
QSize BorderLayout::calculateSize(SizeType sizeType) const
{
    QSize totalSize;

    for(int i=0; i<list.size(); i++) {
        ItemWrapper *wrapper = list.at(i);
        Position position = wrapper->position;
        QSize itemSize;

        if(sizeType == MinimumSize)
            itemSize = wrapper->item->minimumSize();
        else
            itemSize = wrapper->item->sizeHint();

        //如果控件竖着放，Layout的纵向距离变大
        if(position == North || position == South || position == Center)
            totalSize.rheight() += itemSize.height();

        //如果控件横着放，Layout的横向距离变大
        if(position == West || position == East || position == Center)
            totalSize.rwidth() += itemSize.width();
    }


    return totalSize;
}

/*
1.BorderLayout::Center
局部变量center 存储
2.BorderLayout::North
item->setGeometry(QRect(0,0,438,14))
northHeight = 14+6 = 20
3.BorderLayout::South
首先item->setGeometry(QRect(0,0,438,14))
southHeight = 14+6= 20
rect.y() + rect.height() - southHeight + spacing() = 0+278-20+6 = 264
然后首先item->setGeometry(QRect(0,264,438,14))

计算
centerHeight = rect.height() - northHeight - southHeight
 = 278 -20 - 20 =238

4.BorderLayout::West
item->setGeometry(QRect(0,20,32,238))
westWidth = 32+6 = 38

5.BorderLayout::East
item->setGeometry(QRect(rect.width() - eastWidth + spacing(),20,32,238))
*/

//计算出整个Layout所使用的矩形大小和每个LayoutItem矩形大小（在坐标轴上）
void BorderLayout::setGeometry(const QRect &rect)
{
    ItemWrapper *center = 0;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;
    int i;

    //返回QMainWindow布局大小（0,0,438,278）
    QLayout::setGeometry(rect);

    /*
    borderLayout->addWidget(centralWidget, BorderLayout::Center);
    borderLayout->addWidget(createLabel("North"), BorderLayout::North);
    borderLayout->addWidget(createLabel("West"), BorderLayout::West);
    borderLayout->addWidget(createLabel("East 1"), BorderLayout::East);
    borderLayout->addWidget(createLabel("East 2") , BorderLayout::East);
    borderLayout->addWidget(createLabel("South"), BorderLayout::South);
    */


    for (i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == North) {
            item->setGeometry(QRect(rect.x(), northHeight, rect.width(),
                                    item->sizeHint().height()));

            northHeight += item->geometry().height() + spacing();
        } else if (position == South) {
            item->setGeometry(QRect(item->geometry().x(),
                                    item->geometry().y(), rect.width(),
                                    item->sizeHint().height()));

            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(rect.x(),
                              rect.y() + rect.height() - southHeight + spacing(),
                              item->geometry().width(),
                              item->geometry().height()));
        } else if (position == Center) {
            center = wrapper;
        }
    }

    centerHeight = rect.height() - northHeight - southHeight;

    for (i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == West) {
            int i1 = rect.x() + westWidth;
            int i2 = item->sizeHint().width();
            int i3 = centerHeight;
            item->setGeometry(QRect(rect.x() + westWidth, northHeight,
                                    item->sizeHint().width(), centerHeight));

            westWidth += item->geometry().width() + spacing();
        } else if (position == East) {
            item->setGeometry(QRect(item->geometry().x(), item->geometry().y(),
                                    item->sizeHint().width(), centerHeight));

            eastWidth += item->geometry().width() + spacing();

            item->setGeometry(QRect(
                              rect.x() + rect.width() - eastWidth + spacing(),
                              northHeight, item->geometry().width(),
                              item->geometry().height()));
        }
    }

    if (center)
        center->item->setGeometry(QRect(westWidth, northHeight,
                                        rect.width() - eastWidth - westWidth,
                                        centerHeight));


}



