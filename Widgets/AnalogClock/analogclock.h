#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

class AnalogClock : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogClock(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    /*
    This event handler can be reimplemented in a subclass to receive paint events passed in event.
    A paint event is a request to repaint all or part of a widget. It can happen for one of the following reasons:
    1.repaint() or update() was invoked,
    2.the widget was obscured and has now been uncovered, or
    3.many other reasons.
    */
signals:

public slots:
};

#endif // ANALOGCLOCK_H
