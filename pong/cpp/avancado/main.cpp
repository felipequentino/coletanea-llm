#include <SFML/Graphics.hpp>
#include <iostream>

// Constantes para facilitar a leitura do código
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float BALL_RADIUS = 10.0f;
const float PADDLE_WIDTH = 10.0f;
const float PADDLE_HEIGHT = 80.0f;
const float PADDLE_SPEED = 400.0f;

// Função para inicializar as configurações do jogo
void initialize(sf::RectangleShape& paddle1, sf::RectangleShape& paddle2, sf::CircleShape& ball, sf::RenderWindow& window) {
    // Configura a janela
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");

    // Configura a raquete 1
    paddle1.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    paddle1.setFillColor(sf::Color::White);
    paddle1.setPosition(10, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);

    // Configura a raquete 2
    paddle2.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    paddle2.setFillColor(sf::Color::White);
    paddle2.setPosition(WINDOW_WIDTH - PADDLE_WIDTH - 10, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);

    // Configura a bola
    ball.setRadius(BALL_RADIUS);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2 - BALL_RADIUS);
}

// Função para atualizar a lógica do jogo
void update(sf::RectangleShape& paddle1, sf::RectangleShape& paddle2, sf::CircleShape& ball, float& ballVelocityX, float& ballVelocityY, float deltaTime) {
    // Movimenta a bola
    ball.move(ballVelocityX * deltaTime, ballVelocityY * deltaTime);

    // Verifica colisão com as paredes
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= WINDOW_HEIGHT - 2 * BALL_RADIUS)
        ballVelocityY = -ballVelocityY;

    // Verifica colisão com as raquetes
    if (ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) || ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()))
        ballVelocityX = -ballVelocityX;
}

// Função para renderizar o jogo
void render(sf::RenderWindow& window, sf::RectangleShape& paddle1, sf::RectangleShape& paddle2, sf::CircleShape& ball) {
    window.clear();

    // Desenha as raquetes e a bola
    window.draw(paddle1);
    window.draw(paddle2);
    window.draw(ball);

    window.display();
}

int main() {
    sf::RenderWindow window;
    sf::RectangleShape paddle1, paddle2;
    sf::CircleShape ball;

    initialize(paddle1, paddle2, ball, window);

    float ballVelocityX = 300.0f;
    float ballVelocityY = 300.0f;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        update(paddle1, paddle2, ball, ballVelocityX, ballVelocityY, deltaTime);
        render(window, paddle1, paddle2, ball);
    }

    return 0;
}
