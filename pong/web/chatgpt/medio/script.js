const ball = document.getElementById('ball');
let ballX = 290;
let ballY = 190;
let ballSpeedX = 3;
let ballSpeedY = 3;

const leftPaddle = document.getElementById('leftPaddle');
const rightPaddle = document.getElementById('rightPaddle');
let leftPaddleY = 160;
let rightPaddleY = 160;
const paddleSpeed = 8;

const keyState = {}; // Armazena o estado das teclas pressionadas

document.addEventListener('keydown', (event) => {
  keyState[event.key] = true;
});

document.addEventListener('keyup', (event) => {
  keyState[event.key] = false;
});

function movePaddles() {
  const topLimit = 0; // Limite superior da tela
  const bottomLimit = 38; // Limite inferior da tela

  // Verifica o estado das teclas pressionadas
  if (keyState['w'] && leftPaddleY > topLimit) {
    leftPaddleY -= paddleSpeed;
  } else if (keyState['s'] && leftPaddleY < bottomLimit - 80) {
    leftPaddleY += paddleSpeed;
  }
  // Simple AI for the right paddle
  if (rightPaddleY + 40 < ballY) {
    rightPaddleY += paddleSpeed;
  } else if (rightPaddleY + 40 > ballY) {
    rightPaddleY -= paddleSpeed;
  }
}

function update() {
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Ball collision with walls
  if (ballY <= 0 || ballY >= 380) {
    ballSpeedY = -ballSpeedY;
  }

  // Ball collision with paddles
  if (
    (ballX <= 30 && ballX >= 20 && ballY >= leftPaddleY && ballY <= leftPaddleY + 80) ||
    (ballX >= 560 && ballX <= 570 && ballY >= rightPaddleY && ballY <= rightPaddleY + 80)
  ) {
    ballSpeedX = -ballSpeedX * 1.1; // Increase ball speed on paddle collision
  }

  // Ball out of bounds
  if (ballX <= 0 || ballX >= 580) {
    ballX = 290;
    ballY = 190;
    ballSpeedX = 3;
    ballSpeedY = 3;
  }

  ball.style.left = ballX + 'px';
  ball.style.top = ballY + 'px';

  leftPaddle.style.top = leftPaddleY + 'px';
  rightPaddle.style.top = rightPaddleY + 'px';
}

function gameLoop() {
  movePaddles();
  update();
  requestAnimationFrame(gameLoop);
}

gameLoop();

// Diminua a sensibilidade do meu controle, quando pressiono W ou S, vou apenas para as extremidades da tela, sem poder controlar a raquete corretamente