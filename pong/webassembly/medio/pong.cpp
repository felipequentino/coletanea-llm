extern "C" {
  struct Ball {
    float x, y, radius;
  };

  struct Paddle {
    float x, y, width, height;
  };

  Ball ball;
  Paddle paddle, aiPaddle;

  // Declarações das funções
  void init();
  void setMouseY(float mouseY);
  void update();
  void moveBall();
  void moveAIPaddle();
  void checkCollision();
  Ball getBall();
  Paddle getPaddle();
  Paddle getAIPaddle();
}

void init() {
  ball = {400.0f, 200.0f, 10.0f};
  paddle = {0.0f, 150.0f, 10.0f, 100.0f};
  aiPaddle = {790.0f, 150.0f, 10.0f, 100.0f};
}

void setMouseY(float mouseY) {
  paddle.y = mouseY - paddle.height / 2;
}

void update() {
  moveBall();
  moveAIPaddle();
  checkCollision();
}

void moveBall() {
ball.x += 5.0f;
ball.y += 5.0f;

if (ball.x - ball.radius < paddle.x + paddle.width &&
    ball.x + ball.radius > paddle.x &&
    ball.y - ball.radius < paddle.y + paddle.height &&
    ball.y + ball.radius > paddle.y) {
    ball.x = paddle.x + paddle.width + ball.radius;
} else if (ball.x - ball.radius < aiPaddle.x + aiPaddle.width &&
            ball.x + ball.radius > aiPaddle.x &&
            ball.y - ball.radius < aiPaddle.y + aiPaddle.height &&
            ball.y + ball.radius > aiPaddle.y) {
    ball.x = aiPaddle.x - ball.radius;
} // GITHUB COPILOT WRITES THIS
// ... rest of the moveBall function remains the same
}
void moveAIPaddle() {
  if (aiPaddle.y + aiPaddle.height / 2 < ball.y) {
    aiPaddle.y += 4.0f;
  } else {
    aiPaddle.y -= 4.0f;
  }
}


void checkCollision() {
if (ball.y - ball.radius < 0.0f) {
    ball.y = ball.radius;
} else if (ball.y + ball.radius > 400.0f) {
    ball.y = 400.0f - ball.radius;
} // GITHUB COPILOT WRITES THIS
// ... rest of the checkCollision function remains the same
}

Ball getBall() {
  return ball;
}

Paddle getPaddle() {
  return paddle;
}

Paddle getAIPaddle() {
  return aiPaddle;
}
