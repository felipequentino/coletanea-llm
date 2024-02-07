#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int PADDLE_SPEED = 5;
const int BALL_SIZE = 20;
const int BALL_SPEED = 5;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

struct Paddle {
    int x, y;
    int dy;
};

struct Ball {
    int x, y;
    int dx, dy;
};

void initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleInput(Paddle& paddle1, Paddle& paddle2) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            close();
            exit(0);
        }
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_UP) {
                paddle2.dy = -PADDLE_SPEED;
            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                paddle2.dy = PADDLE_SPEED;
            }
            if (e.key.keysym.sym == SDLK_w) {
                paddle1.dy = -PADDLE_SPEED;
            }
            if (e.key.keysym.sym == SDLK_s) {
                paddle1.dy = PADDLE_SPEED;
            }
        }
        if (e.type == SDL_KEYUP) {
            if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN) {
                paddle2.dy = 0;
            }
            if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s) {
                paddle1.dy = 0;
            }
        }
    }
}

void update(Paddle& paddle1, Paddle& paddle2, Ball& ball) {
    paddle1.y += paddle1.dy;
    paddle2.y += paddle2.dy;

    ball.x += ball.dx;
    ball.y += ball.dy;

    if (ball.y <= 0 || ball.y + BALL_SIZE >= SCREEN_HEIGHT) {
        ball.dy = -ball.dy;
    }

    if ((ball.x <= PADDLE_WIDTH && ball.y >= paddle1.y && ball.y <= paddle1.y + PADDLE_HEIGHT) ||
        (ball.x + BALL_SIZE >= SCREEN_WIDTH - PADDLE_WIDTH && ball.y >= paddle2.y && ball.y <= paddle2.y + PADDLE_HEIGHT)) {
        ball.dx = -ball.dx;
    }
}

void render(const Paddle& paddle1, const Paddle& paddle2, const Ball& ball) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect paddleRect1 = {paddle1.x, paddle1.y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleRect1);

    SDL_Rect paddleRect2 = {SCREEN_WIDTH - PADDLE_WIDTH, paddle2.y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddleRect2);

    SDL_Rect ballRect = {ball.x, ball.y, BALL_SIZE, BALL_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ballRect);

    SDL_RenderPresent(renderer);
}

int main() {
    initialize();

    Paddle paddle1 = {50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, 0};
    Paddle paddle2 = {SCREEN_WIDTH - PADDLE_WIDTH - 50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, 0};
    Ball ball = {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SPEED, BALL_SPEED};

    bool quit = false;
    while (!quit) {
        handleInput(paddle1, paddle2);
        update(paddle1, paddle2, ball);
        render(paddle1, paddle2, ball);
        SDL_Delay(10);
    }

    close();
    return 0;
}
