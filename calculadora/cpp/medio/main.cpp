#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <cmath>

class Calculator : public QWidget {
    Q_OBJECT
public:
    Calculator(QWidget *parent = 0) : QWidget(parent) {
        QGridLayout *layout = new QGridLayout;
        display = new QLineEdit();
        display->setAlignment(Qt::AlignRight);
        display->setReadOnly(true);
        layout->addWidget(display, 0, 0, 1, 4);

        const char *buttons[6][4] = {
            {"7", "8", "9", "/"},
            {"4", "5", "6", "*"},
            {"1", "2", "3", "-"},
            {"0", ".", "=", "+"},
            {"sqrt", "pow", "sin", "cos"},
            {"log", "Mem+", "Mem-", "Mem"}
        };

        for(int i = 0; i < 6; ++i) {
            for(int j = 0; j < 4; ++j) {
                QPushButton *button = new QPushButton(buttons[i][j]);
                connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
                layout->addWidget(button, i + 1, j);
            }
        }

        setLayout(layout);
    }

public slots:
    void buttonClicked() {
        QPushButton *button = qobject_cast<QPushButton *>(sender());
        QString buttonText = button->text();
        QString currentValue = display->text();

        if(buttonText == "=") {
            // Evaluate expression
            QString result = evaluateExpression(currentValue);
            display->setText(result);
        } else if(buttonText == "sqrt") {
            // Square root
            double value = currentValue.toDouble();
            double sqrtValue = sqrt(value);
            display->setText(QString::number(sqrtValue));
        } else if(buttonText == "pow") {
            // Power
            // Implementation of power function
            double base = parseExpression(currentValue.section('^', 0, 0));
            double exponent = parseExpression(currentValue.section('^', 1));
            double powValue = pow(base, exponent);
            display->setText(QString::number(powValue));
        } else if(buttonText == "sin") {
            // Sine
            double value = parseExpression(currentValue);
            double sinValue = sin(value * M_PI / 180.0); // Convert to radians
            display->setText(QString::number(sinValue));
        } else if(buttonText == "cos") {
            // Cosine
            double value = parseExpression(currentValue);
            double cosValue = cos(value * M_PI / 180.0); // Convert to radians
            display->setText(QString::number(cosValue));
        } else if(buttonText == "log") {
            // Logarithm
            double value = parseExpression(currentValue);
            double logValue = log10(value);
            display->setText(QString::number(logValue));
        } else if(buttonText == "Mem+") {
            // Add to memory
            memory += currentValue.toDouble();
        } else if(buttonText == "Mem-") {
            // Subtract from memory
            memory -= currentValue.toDouble();
        } else if(buttonText == "Mem") {
            // Retrieve memory
            display->setText(QString::number(memory));
        } else {
            // Append digits and operators to the display
            display->setText(currentValue + buttonText);
        }
    }

    QString evaluateExpression(const QString &expression) {
        // Evaluate the expression and return the result
    }

    double parseExpression(const QString &expression) {
        return expression.toDouble();
    }

private:
    QLineEdit *display;
    double memory = 0.0;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator calculator;
    calculator.setWindowTitle("Calculator");
    calculator.show();
    return app.exec();
}

#include "main.moc"
