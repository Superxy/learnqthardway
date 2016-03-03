#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT

public:
    /*
        The Button class has a convenience constructor that takes a text label and a parent widget,
        and it reimplements QWidget::sizeHint() to provide more space around the text than the amount
        QToolButton normally provides.
    */
    explicit Button(const QString &text, QWidget *parent = 0);
    QSize sizeHint() const;
};

/*
 *  QWidget::sizeHint()
    sizeHint::const QSize
    This property holds the recommended size for the widget.
    If the value of this property is an invalid size, no size is recommended.
    The default implementation of sizeHint() returns an invalid size if there is
    no layout for this widget, and returns the layout's preferred size otherwise.
*/

#endif // BUTTON_H
