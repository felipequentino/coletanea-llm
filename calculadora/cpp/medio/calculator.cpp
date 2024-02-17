#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <cmath>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        setupSignalsAndSlots();
    }

private slots:
    void calculateResult() {
        // Obtem os valores dos campos de entrada
        double num1 = num1Edit->text().toDouble();
        double num2 = num2Edit->text().toDouble();

        // Realiza a operação selecionada
        double result;
        QString operation = operationComboBox->currentText();
        if (operation == "+") {
            result = num1 + num2;
        } else if (operation == "-") {
            result = num1 - num2;
        } else if (operation == "*") {
            result = num1 * num2;
        } else if (operation == "/") {
            if (num2 == 0) {
                QMessageBox::warning(this, "Erro", "Divisão por zero!");
                return;
            }
            result = num1 / num2;
        } else if (operation == "^") {
            result = std::pow(num1, num2);
        } else if (operation == "sqrt") {
            if (num2 < 0) {
                QMessageBox::warning(this, "Erro", "Raiz quadrada de número negativo!");
                return;
            }
            result = std::sqrt(num2);
        }

        // Exibe o resultado
        resultLabel->setText("Resultado: " + QString::number(result));
    }

private:
    void setupUI() {
        // Layout
        QGridLayout *layout = new QGridLayout(this);

        // Campos de entrada
        num1Edit = new QLineEdit(this);
        num2Edit = new QLineEdit(this);

        // Operações
        operationComboBox = new QComboBox(this);
        operationComboBox->addItem("+");
        operationComboBox->addItem("-");
        operationComboBox->addItem("*");
        operationComboBox->addItem("/");
        operationComboBox->addItem("^");
        operationComboBox->addItem("sqrt");

        // Botão calcular
        QPushButton *calculateButton = new QPushButton("Calcular", this);

        // Resultado
        resultLabel = new QLabel("Resultado: ", this);

        // Adiciona widgets ao layout
        layout->addWidget(num1Edit, 0, 0);
        layout->addWidget(operationComboBox, 0, 1);
        layout->addWidget(num2Edit, 0, 2);
        layout->addWidget(calculateButton, 1, 0, 1, 3);
        layout->addWidget(resultLabel, 2, 0, 1, 3);

        setLayout(layout);
    }

    void setupSignalsAndSlots() {
        connect(calculateButton, &QPushButton::clicked, this, &Calculator::calculateResult);
    }

    QLineEdit *num1Edit;
    QLineEdit *num2Edit;
    QComboBox *operationComboBox;
    QLabel *resultLabel;
    QPushButton *calculateButton;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calculator;
    calculator.show();

    return app.exec();
}

#include "main.moc"
