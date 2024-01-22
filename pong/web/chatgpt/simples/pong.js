// pong.js

// Constantes e variáveis do jogo
const gameContainer = document.getElementById("game");
const ball = document.getElementById("ball");
const leftPaddle = document.getElementById("leftPaddle");
const rightPaddle = document.getElementById("rightPaddle");

let ballX = 290;
let ballY = 190;
let ballSpeedX = 3;
let ballSpeedY = 3;
let leftPaddleY = 160;
let rightPaddleY = 160;
const paddleSpeed = 10;

// Função para atualizar a posição da bola
function moveBall() {
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Colisão com paredes superior e inferior
  if (ballY >= 385 || ballY <= 0) {
    ballSpeedY = -ballSpeedY;
  }

  // Colisão com as pás
  if (
    ballX <= 25 &&
    ballY >= leftPaddleY &&
    ballY <= leftPaddleY + 80
  ) {
    ballSpeedX = -ballSpeedX;
  }

  if (
    ballX >= 560 &&
    ballY >= rightPaddleY &&
    ballY <= rightPaddleY + 80
  ) {
    ballSpeedX = -ballSpeedX;
  }

  // Se a bola passar das pás
  if (ballX < 0 || ballX > 600) {
    ballX = 290;
    ballY = 190;
    ballSpeedX = -ballSpeedX;
  }

  ball.style.left = ballX + "px";
  ball.style.top = ballY + "px";
}

// Função para mover as pás
function movePaddles() {
  document.addEventListener("keydown", function (event) {
    if (event.key === "ArrowUp" && rightPaddleY > 0) {
      rightPaddleY -= paddleSpeed;
    } else if (event.key === "ArrowDown" && rightPaddleY < 320) {
      rightPaddleY += paddleSpeed;
    }

    if (event.key === "w" && leftPaddleY > 0) {
      leftPaddleY -= paddleSpeed;
    } else if (event.key === "s" && leftPaddleY < 320) {
      leftPaddleY += paddleSpeed;
    }

    leftPaddle.style.top = leftPaddleY + "px";
    rightPaddle.style.top = rightPaddleY + "px";
  });
}

// Função de loop do jogo
function gameLoop() {
  moveBall();
  movePaddles();
  requestAnimationFrame(gameLoop);
}

// Iniciar o loop do jogo
gameLoop();
