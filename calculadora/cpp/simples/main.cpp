#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Calculator {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text displayText;
    std::string displayStr;

    enum class Operator {
        None,
        Addition,
        Subtraction,
        Multiplication,
        Division
    } currentOperator;

    double firstOperand;
    double secondOperand;

    void processInput(sf::Event event) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::TextEntered) {
            if (std::isdigit(event.text.unicode) || event.text.unicode == '.') {
                displayStr += static_cast<char>(event.text.unicode);
                updateDisplay();
            } else if (event.text.unicode == '\b' && displayStr.size() > 0) {
                displayStr.pop_back();
                updateDisplay();
            } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                evaluate();
            }
        }
    }

    void updateDisplay() {
        displayText.setString(displayStr);
    }

    void evaluate() {
        secondOperand = std::stod(displayStr);
        double result;
        switch (currentOperator) {
            case Operator::Addition:
                result = firstOperand + secondOperand;
                break;
            case Operator::Subtraction:
                result = firstOperand - secondOperand;
                break;
            case Operator::Multiplication:
                result = firstOperand * secondOperand;
                break;
            case Operator::Division:
                result = firstOperand / secondOperand;
                break;
            default:
                result = secondOperand;
                break;
        }
        displayStr = std::to_string(result);
        updateDisplay();
        firstOperand = result;
    }

public:
    Calculator() : window(sf::VideoMode(300, 400), "SFML Calculator"), currentOperator(Operator::None), firstOperand(0), secondOperand(0) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
        }
        displayText.setFont(font);
        displayText.setCharacterSize(24);
        displayText.setPosition(10, 10);
        displayText.setFillColor(sf::Color::White);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                processInput(event);
            }

            window.clear(sf::Color::Black);
            window.draw(displayText);
            window.display();
        }
    }

    void setOperator(Operator op) {
        currentOperator = op;
        firstOperand = std::stod(displayStr);
        displayStr = "";
        updateDisplay();
    }
};

int main() {
    Calculator calc;
    calc.run();

    return 0;
}
