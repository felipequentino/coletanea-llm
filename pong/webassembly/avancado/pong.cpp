#include <emscripten/emscripten.h>
#include <cstdlib>
#include <ctime>

float paddle1Y = 0.0;
float paddle2Y = 0.0;
float ballX = 0.0;
float ballY = 0.0;
float ballSpeedX = 0.0;
float ballSpeedY = 0.0;

float getRandomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    float get_paddle1_position() {
        return paddle1Y;
    }

    EMSCRIPTEN_KEEPALIVE
    void set_paddle1_position(float position) {
        paddle1Y = position;
    }

    EMSCRIPTEN_KEEPALIVE
    void update_game_state() {
        // Atualiza o estado do jogo, como a posição da bola e a lógica da IA

        // Simplesmente move a bola para frente
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // Implementa uma IA básica para a raquete 2 (oponente)
        float paddle2Speed = 0.05;
        if (ballY > paddle2Y + 50) {
            paddle2Y += paddle2Speed;
        } else {
            paddle2Y -= paddle2Speed;
        }

        // Adiciona alguma variação à força da rebatida
        float hitVariation = getRandomFloat(-0.2, 0.2);
        ballSpeedY += hitVariation;

        // Simplesmente rebata a bola na borda superior e inferior da tela
        if (ballY > 390 || ballY < 10) {
            ballSpeedY = -ballSpeedY;
        }
    }

    EMSCRIPTEN_KEEPALIVE
    float get_paddle2_position() {
        return paddle2Y;
    }

    EMSCRIPTEN_KEEPALIVE
    float get_ball_position_x() {
        return ballX;
    }

    EMSCRIPTEN_KEEPALIVE
    float get_ball_position_y() {
        return ballY;
    }

    EMSCRIPTEN_KEEPALIVE
    void set_ball_speed(float speedX, float speedY) {
        ballSpeedX = speedX;
        ballSpeedY = speedY;
    }

    // Função para reiniciar o jogo
    EMSCRIPTEN_KEEPALIVE
    void reset_game() {
        paddle1Y = 0.0;
        paddle2Y = 0.0;
        ballX = 0.0;
        ballY = 0.0;
        ballSpeedX = 0.0;
        ballSpeedY = 0.0;
    }
}
