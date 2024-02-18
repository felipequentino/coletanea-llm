#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ToDoList {
private:
    sf::Font font;
    std::vector<std::string> tasks;

public:
    ToDoList() {
        if (!font.loadFromFile("arial.ttf")) {
            // handle error if font loading fails
        }
    }

    void addTask(const std::string& task) {
        tasks.push_back(task);
    }

    void draw(sf::RenderWindow& window) {
        window.clear(sf::Color::White);

        for (size_t i = 0; i < tasks.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(tasks[i]);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Black);
            text.setPosition(10, i * 30);
            window.draw(text);
        }

        window.display();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 300), "To-Do List");
    ToDoList toDoList;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Add tasks (dummy example)
        toDoList.addTask("Task 1");
        toDoList.addTask("Task 2");
        toDoList.addTask("Task 3");

        toDoList.draw(window);
    }

    return 0;
}
