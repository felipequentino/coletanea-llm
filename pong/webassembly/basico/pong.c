#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <stdio.h>

// Variáveis do jogo
float paddleY = 50.0f;
float paddleSpeed = 5.0f;
float ballX = 400.0f;
float ballY = 300.0f;
float ballSpeedX = 5.0f;
float ballSpeedY = 2.0f;

// Função de atualização do jogo
EMSCRIPTEN_KEEPALIVE
void updateGame() {
    // Atualizar a posição da raquete
    paddleY += paddleSpeed;

    // Verificar limites da raquete
    if (paddleY < 0) paddleY = 0;
    if (paddleY > 500) paddleY = 500;

    // Atualizar a posição da bola
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Verificar colisão com as paredes verticais
    if (ballY < 0 || ballY > 590) {
        ballSpeedY = -ballSpeedY;
    }

    // Verificar colisão com a raquete
    if (ballX > 780 && ballX < 800 && ballY > paddleY && ballY < paddleY + 100) {
        ballSpeedX = -ballSpeedX;
    }

    // Verificar se a bola ultrapassou a raquete
    if (ballX > 800) {
        // Resetar a posição da bola
        ballX = 400.0f;
        ballY = 300.0f;

        // Mudar a direção da bola
        ballSpeedX = -ballSpeedX;
    }

    // Chamar função JavaScript para renderizar
    char script[50];
    sprintf(script, "renderGame(%f, %f)", ballX, ballY);
    emscripten_run_script(script);
}

// Função principal
int main() {
    // Iniciar o loop de atualização
    emscripten_set_main_loop(updateGame, 60, 1);

    return 0;
}
