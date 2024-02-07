#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <termios.h>
#include <fcntl.h>

using namespace std;

const int WIDTH = 60;
const int HEIGHT = 20;
const char PLAYER1 = 'A';
const char PLAYER2 = 'B';
const char BALL = '*';
const char EMPTY = ' ';

class PongGame {
private:
    int player1Y, player2Y;
    int ballX, ballY;
    int ballDirX, ballDirY;
    int ballSpeed;
    int player1Score, player2Score;
    bool gameOver;

public:
    PongGame() {
        player1Y = HEIGHT / 2;
        player2Y = HEIGHT / 2;
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
        ballDirX = -1;
        ballDirY = 0;
        ballSpeed = 100;
        player1Score = 0;
        player2Score = 0;
        gameOver = false;
    }

    void draw() {
        system("clear");
        for (int i = 0; i < WIDTH + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (j == 0)
                    cout << "#";
                if (i == player1Y && j == 0)
                    cout << PLAYER1;
                else if (i == player2Y && j == WIDTH - 1)
                    cout << PLAYER2;
                else if (i == ballY && j == ballX)
                    cout << BALL;
                else
                    cout << EMPTY;
                if (j == WIDTH - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < WIDTH + 2; i++)
            cout << "#";
        cout << endl;

        cout << "Player A: " << player1Score << "   Player B: " << player2Score << endl;
    }

    void input() {
        char input;
        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == 'w' && player1Y > 0)
                player1Y--;
            if (input == 's' && player1Y < HEIGHT - 1)
                player1Y++;
        }
    }

    void update() {
        // AI for player 2
        if (ballY < player2Y && player2Y > 0)
            player2Y--;
        else if (ballY > player2Y && player2Y < HEIGHT - 1)
            player2Y++;

        // Ball movement
        ballX += ballDirX;
        ballY += ballDirY;

        // Ball collisions
        if (ballY == 0 || ballY == HEIGHT - 1)
            ballDirY = -ballDirY;

        if (ballX == 1 && ballY == player1Y)
            ballDirX = -ballDirX;
        else if (ballX == WIDTH - 2 && ballY == player2Y)
            ballDirX = -ballDirX;

        // Ball scoring
        if (ballX == 0) {
            player2Score++;
            reset();
        } else if (ballX == WIDTH - 1) {
            player1Score++;
            reset();
        }

        // Increase ball speed
        if (ballSpeed > 10)
            ballSpeed--;

        usleep(ballSpeed * 1000);
    }

    void reset() {
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
        ballDirX = -ballDirX;
        ballSpeed = 100;
    }

    bool isGameOver() {
        return gameOver;
    }
};

// Função para configurar a entrada de teclado no modo não-bloqueante
void setNonBlockingInput() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    setNonBlockingInput();
    PongGame game;

    while (!game.isGameOver()) {
        game.draw();
        game.input();
        game.update();
    }

    return 0;
}
