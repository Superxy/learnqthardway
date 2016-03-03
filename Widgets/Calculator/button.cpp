#include "button.h"

Button::Button(const QString &text, QWidget *parent) : QToolButton(parent)
{
    /*
    The buttons' appearance is determined by the layout of the calculator widget through
    the size and size policy of the layout's child widgets. The call to the setSizePolicy()
    function in the constructor ensures that the button will expand horizontally to fill all
    the available space; by default, QToolButtons don't expand to fill available space.
    Without this call, the different buttons in a same column would have different widths.
    */
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);

}

QSize Button::sizeHint() const
{
    /*
    In sizeHint(), we try to return a size that looks good for most buttons.
    We reuse the size hint of the base class (QToolButton) but modify it in the following ways:
        1.We add 20 to the height component of the size hint.
        2.We make the width component of the size hint at least as much as the height.

    This ensures that with most fonts, the digit and operator buttons will be square,
    without truncating the text on the Backspace, Clear, and Clear All buttons.
    */
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;  // reference to the height.
    size.rwidth() = qMax(size.width(), size.height());  // reference to the width
    return size;
}


