#include "analogclock.h"
#include <QtWidgets>

AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent)
{
    QTimer *timer = new QTimer(this); // timer's parent is AnalogClock
    /*
    void QTimer::timeout()  [signal]
    This signal is emitted when the timer times out.
    Note: This is a private signal. It can be used in signal connections but cannot be emitted by the user.
    */
    /*
    void QWidget::update() [slot]
    Updates the widget unless updates are disabled or the widget is hidden.
    This function does not cause an immediate repaint; instead it schedules a paint event for processing
    when Qt returns to the main event loop. This permits Qt to optimize for more speed and less flicker
    than a call to repaint() does.

    Calling update() several times normally results in just one paintEvent() call.

    Qt normally erases the widget's area before the paintEvent() call. If the Qt::WA_OpaquePaintEvent
    widget attribute is set, the widget is responsible for painting all its pixels with an opaque color.
    */
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    /*
    void QTimer::start(int msec)  [slot]
    Starts or restarts the timer with a timeout interval of msec milliseconds.
    If the timer is already running, it will be stopped and restarted.
    If singleShot is true, the timer will be activated only once.
    */
    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    /*
    void QWidget::resize(int w, int h)
    This is an overloaded function.
    This corresponds to resize(QSize(w, h)).
    */
    resize(200, 200);

}

void AnalogClock::paintEvent(QPaintEvent *event)
{
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };

    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 129, 127, 191);

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    /*
    Sets the given render hint on the painter if on is true; otherwise clears the render hint.
    */
    painter.setRenderHint(QPainter::Antialiasing);
    /*
    Translates the coordinate system by the given offset; i.e. the given offset is added to points.
    */
    painter.translate(width()/2, height()/2);
    /*
    Scales the coordinate system by (sx, sy).
    */
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    /*
    Saves the current painter state (pushes the state onto a stack). A save() must be followed by
    a corresponding restore(); the end() function unwinds the stack.
    */
    painter.save();
    /*
    Rotates the coordinate system clockwise. The given angle parameter uses degree unit.
    */
    painter.rotate(30.0 * (time.hour() + time.minute()/60.0));
    /*
    This is an overloaded function.
    Draws the convex polygon defined by the first pointCount points in the array points using the current pen.
    */
    painter.drawConvexPolygon(hourHand, 3);
    /*
    Restores the current painter state (pops a saved state off the stack).
    */
    painter.restore();

    painter.setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
}
