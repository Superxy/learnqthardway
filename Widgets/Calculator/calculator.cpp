#include "calculator.h"
#include "button.h"
#include <QtWidgets>

Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;
    /*
    In the constructor, we initialize the calculator's state.
    The pendingAdditiveOperator and pendingMultiplicativeOperator variables don't need to
    be initialized explicitly, because the QString constructor initializes them to empty strings.
    */

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize()+8);
    display->setFont(font);

    /*
    We create the QLineEdit representing the calculator's display and set up some of its properties.
    In particular, we set it to be read-only.
    We also enlarge display's font by 8 points.
    */

    for(int i=0; i<numDigitButton; i++)
    {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    /*
    For each button, we call the private createButton() function with the proper text
    label and a slot to connect to the button.
    */
    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked())); // +-

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    Button *clearButton = createButton(tr("Clear"), SLOT(clear()));
    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));

    Button *clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
    Button *readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
    Button *setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
    Button *addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

    Button *divisionButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClicked())); // division
    Button *timesButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClicked())); //multiply
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

    Button *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    Button *powerButton = createButton(tr("x\302\262"), SLOT(unaryOperatorClicked())); //  x square
    Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);

    for (int i = 1; i < numDigitButton; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);
    setLayout(mainLayout);

    /*
    The layout is handled by a single QGridLayout.
    The QLayout::setSizeConstraint() call ensures that the Calculator widget is
    always shown as its optimal size (its size hint), preventing the user from
    resizing the calculator. The size hint is determined by the size and size policy
    of the child widgets.
    */
    /*
    Most child widgets occupy only one cell in the grid layout.
    For these, we only need to pass a row and a column to QGridLayout::addWidget().
    The display, backspaceButton, clearButton, and clearAllButton widgets occupy more
    than one column; for these we must also pass a row span and a column span.
    */

    setWindowTitle(tr("Calculator"));
}

/*
    The private createButton() function is called from the constructor to create calculator buttons.
*/
Button *Calculator::createButton(const QString &test, const char *member)
{
    Button *button = new Button(test);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

/*
Pressing one of the calculator's digit buttons will emit the button's clicked() signal,
which will trigger the digitClicked() slot.First, we find out which button sent the signal
using QObject::sender(). This function returns the sender as a QObject pointer. Since we know
that the sender is a Button object, we can safely cast the QObject. We could have used a C-style
cast or a C++ static_cast<>(), but as a defensive programming technique we use a qobject_cast().
The advantage is that if the object has the wrong type, a null pointer is returned. Crashes due
to null pointers are much easier to diagnose than crashes due to unsafe casts. Once we have the
button, we extract the operator using QToolButton::text().The slot needs to consider two situations
in particular. If display contains "0" and the user clicks the 0 button, it would be silly to show
"00". And if the calculator is in a state where it is waiting for a new operand, the new digit is
the first digit of that new operand; in that case, any result of a previous calculation must be
cleared first.At the end, we append the new digit to the value in the display.
*/
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    /*
    QObject::sender()
    Returns a pointer to the object that sent the signal,
    if called in a slot activated by a signal; otherwise it returns 0.
    */
    int digitValue = clickedButton->text().toInt();  //0~9
    if (display->text() == "0" && digitValue == 0.0)  // no duplicate 0
        return;

    if (waitingForOperand) {
        display->clear();
        /*
        void QLineEdit::clear()
        Clears the contents of the line edit.
        */
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}
/*
The unaryOperatorClicked() slot is called whenever one of the unary operator buttons is clicked.
Again a pointer to the clicked button is retrieved using QObject::sender(). The operator is
extracted from the button's text and stored in clickedOperator. The operand is obtained from
display.Then we perform the operation. If Sqrt is applied to a negative number or 1/x to zero,
we call abortOperation(). If everything goes well, we display the result of the operation
in the line edit and we set waitingForOperand to true. This ensures that if the user types
a new digit, the digit will be considered as a new operand, instead of being appended to the
current value.
*/
void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

/*
The additiveOperatorClicked() slot is called when the user clicks the + or - button.
Before we can actually do something about the clicked operator, we must handle any pending
operations. We start with the multiplicative operators, since these have higher precedence
than additive operators:
*/
void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
               abortOperation();
               return;
        }
    display->setText(QString::number(factorSoFar));
    operand = factorSoFar;
    factorSoFar = 0.0;
    pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
            if (!calculate(operand, pendingAdditiveOperator)) {
                abortOperation();
                return;
            }
            display->setText(QString::number(sumSoFar));
        } else {
            sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
        waitingForOperand = true;
}


void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains("."))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}

void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void Calculator::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}

void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}





