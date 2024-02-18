#include <QtWidgets>

class Calculator : public QMainWindow {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
    }

private slots:
    void digitClicked();
    void operationClicked();
    void clear();
    void equalsClicked();

private:
    QLineEdit *display;
    QPushButton *buttons[10];
    QPushButton *addButton, *subButton, *mulButton, *divButton;
    QPushButton *powButton, *sqrtButton, *sinButton, *cosButton, *tanButton;
    QPushButton *logButton, *factButton;
    QPushButton *clearButton, *equalsButton;
    QGridLayout *mainLayout;

    void setupUI();
    QPushButton *createButton(const QString &text);

    double memory;
    QString currentOperation;
    bool waitingForOperand;

    double evaluateBinaryOperation(double leftOperand, double rightOperand, const QString &operation);

    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) { return a / b; }
    double power(double base, double exponent) { return std::pow(base, exponent); }
    double squareRoot(double num) { return std::sqrt(num); }
    double sine(double angle) { return std::sin(angle); }
    double cosine(double angle) { return std::cos(angle); }
    double tangent(double angle) { return std::tan(angle); }
    double logarithm(double base, double num) { return std::log(num) / std::log(base); }
    double factorial(double num) {
        double result = 1;
        for (int i = 1; i <= num; ++i) {
            result *= i;
        }
        return result;
    }
};

void Calculator::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    display = new QLineEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    mainLayout = new QGridLayout();
    centralWidget->setLayout(mainLayout);

    mainLayout->addWidget(display, 0, 0, 1, 4);

    for (int i = 0; i < 10; ++i) {
        buttons[i] = createButton(QString::number(i));
        mainLayout->addWidget(buttons[i], 3 - i / 3, i % 3);
        connect(buttons[i], &QPushButton::clicked, this, &Calculator::digitClicked);
    }

    addButton = createButton("+");
    subButton = createButton("-");
    mulButton = createButton("*");
    divButton = createButton("/");
    powButton = createButton("^");
    sqrtButton = createButton("sqrt");
    sinButton = createButton("sin");
    cosButton = createButton("cos");
    tanButton = createButton("tan");
    logButton = createButton("log");
    factButton = createButton("!");

    mainLayout->addWidget(addButton, 1, 3);
    mainLayout->addWidget(subButton, 2, 3);
    mainLayout->addWidget(mulButton, 3, 3);
    mainLayout->addWidget(divButton, 4, 3);
    mainLayout->addWidget(powButton, 4, 2);
    mainLayout->addWidget(sqrtButton, 4, 1);
    mainLayout->addWidget(sinButton, 1, 4);
    mainLayout->addWidget(cosButton, 2, 4);
    mainLayout->addWidget(tanButton, 3, 4);
    mainLayout->addWidget(logButton, 4, 4);
    mainLayout->addWidget(factButton, 5, 3);

    clearButton = createButton("C");
    equalsButton = createButton("=");
    mainLayout->addWidget(clearButton, 1, 0);
    mainLayout->addWidget(equalsButton, 5, 0);

    connect(addButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(subButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(mulButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(divButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(powButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(sqrtButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(sinButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(cosButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(tanButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(logButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(factButton, &QPushButton::clicked, this, &Calculator::operationClicked);

    connect(clearButton, &QPushButton::clicked, this, &Calculator::clear);
    connect(equalsButton, &QPushButton::clicked, this, &Calculator::equalsClicked);

    setStyleSheet("QPushButton { min-width: 50px; min-height: 50px; font-size: 18px; }"
                  "QLineEdit { min-height: 50px; font-size: 24px; }");

    memory = 0.0;
    currentOperation = "";
    waitingForOperand = true;
}

QPushButton *Calculator::createButton(const QString &text) {
    QPushButton *button = new QPushButton(text);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return button;
}

double Calculator::evaluateBinaryOperation(double leftOperand, double rightOperand, const QString &operation) {
    if (operation == "+") return add(leftOperand, rightOperand);
    else if (operation == "-") return subtract(leftOperand, rightOperand);
    else if (operation == "*") return multiply(leftOperand, rightOperand);
    else if (operation == "/") return divide(leftOperand, rightOperand);
    else if (operation == "^") return power(leftOperand, rightOperand);
    else return 0.0; // Placeholder for other operations
}

void Calculator::digitClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString digit = clickedButton->text();
    QString currentText = display->text();

    if (currentText == "0" || waitingForOperand) {
        display->setText(digit);
        waitingForOperand = false;
    } else {
        display->setText(currentText + digit);
    }
}

void Calculator::operationClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString operation = clickedButton->text();
    double operand = display->text().toDouble();

    if (!currentOperation.isEmpty()) {
        double result = evaluateBinaryOperation(memory, operand, currentOperation);
        display->setText(QString::number(result));
        waitingForOperand = true;
        currentOperation = "";
    } else {
        memory = operand;
        waitingForOperand = true;
        currentOperation = operation;
    }
}

void Calculator::clear() {
    display->clear();
    memory = 0.0;
    currentOperation = "";
    waitingForOperand = true;
}

void Calculator::equalsClicked() {
    double operand = display->text().toDouble();
    double result = evaluateBinaryOperation(memory, operand, currentOperation);
    display->setText(QString::number(result));
    waitingForOperand = true;
    currentOperation = "";
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator calculator;
    calculator.show();
    return app.exec();
}

#include "main.moc"
