#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Calculator {
private:
    sf::Font font;
    sf::Text displayText;
    std::string inputBuffer;

public:
    Calculator() {
        font.loadFromFile("arial.ttf");
        displayText.setFont(font);
        displayText.setCharacterSize(24);
        displayText.setFillColor(sf::Color::Black);
        displayText.setPosition(10, 10);
        inputBuffer = "0";
        updateDisplay();
    }

    void handleInput(sf::Event event) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                inputBuffer += event.key.code - sf::Keyboard::Num0 + '0';
            } else if (event.key.code == sf::Keyboard::Add) {
                inputBuffer += "+";
            } else if (event.key.code == sf::Keyboard::Subtract) {
                inputBuffer += "-";
            } else if (event.key.code == sf::Keyboard::Multiply) {
                inputBuffer += "*";
            } else if (event.key.code == sf::Keyboard::Divide) {
                inputBuffer += "/";
            } else if (event.key.code == sf::Keyboard::Enter) {
                evaluate();
            }
            updateDisplay();
        }
    }

    void evaluate() {
        std::stringstream ss(inputBuffer);
        double result;
        ss >> result;
        while (ss) {
            char op;
            double operand;
            ss >> op >> operand;
            switch (op) {
                case '+':
                    result += operand;
                    break;
                case '-':
                    result -= operand;
                    break;
                case '*':
                    result *= operand;
                    break;
                case '/':
                    if (operand != 0)
                        result /= operand;
                    else
                        inputBuffer = "Error";
                    break;
                default:
                    inputBuffer = "Error";
                    break;
            }
        }
        inputBuffer = std::to_string(result);
    }

    void updateDisplay() {
        displayText.setString(inputBuffer);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(displayText);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 400), "Calculator");
    Calculator calculator;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            calculator.handleInput(event);
        }

        window.clear(sf::Color::White);
        calculator.draw(window);
        window.display();
    }

    return 0;
}
