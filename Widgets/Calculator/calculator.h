#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
class Button;
class QLineEdit;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);

private slots:
    void digitClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();
    /*
    Buttons are grouped in categories according to their behavior.
    digit buttons (labeled 0 to 9) append a digit to the current operand.
    we connect multiple buttons to the same slot (e.g., digitClicked()).
    The categories are digits, unary operators (Sqrt, x², 1/x), additive operators (+, -),
    and multiplicative operators (×, ÷). The other buttons have their own slots.
    */
private:
    Button *createButton(const QString &test,const char *member);
    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);
    /*
    The private createButton() function is used as part of the widget construction.
    abortOperation() is called whenever a division by zero occurs or when a square root operation is applied to a negative number.
    calculate() applies a binary operator (+, -, ×, or ÷).
    */

    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    /*
    sumInMemory contains the value stored in the calculator's memory (using MS, M+, or MC).
    sumSoFar stores the value accumulated so far. When the user clicks =, sumSoFar is recomputed and shown on the display.
    Clear All resets sumSoFar to zero.
    factorSoFar stores a temporary value when doing multiplications and divisions.
    pendingAdditiveOperator stores the last additive operator clicked by the user.
    pendingMultiplicativeOperator stores the last multiplicative operator clicked by the user.
    waitingForOperand is true when the calculator is expecting the user to start typing an operand.
    */

    QLineEdit *display;
    enum { numDigitButton = 10 };
    Button *digitButtons[numDigitButton];
    /*
    Finally, we declare the variables associated with the display and the buttons used to display numerals.
    */

};

#endif // CALCULATOR_H
