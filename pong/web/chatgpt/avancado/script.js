// Código JavaScript para o jogo
const ball = document.querySelector('.ball');
const paddles = document.querySelectorAll('.paddle');
const player1 = document.getElementById('player1');
const player2 = document.getElementById('player2');

const container = document.querySelector('.game-container');
const controls = document.querySelector('.controls');

const containerHeight = document.querySelector('.game-container').offsetHeight;
const containerWidth = document.querySelector('.game-container').offsetWidth;

let ballX = containerWidth / 2;
let ballY = containerHeight / 2;
let ballSpeedX = 5;
let ballSpeedY = 5;

let player1Y = containerHeight / 2 - paddles[0].offsetHeight / 2;
let player2Y = containerHeight / 2 - paddles[1].offsetHeight / 2;

function update() {
  // Atualização da bola
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Verificação de colisão com as bordas verticais
  if (ballY <= 0 || ballY >= containerHeight - ball.offsetHeight) {
    ballSpeedY = -ballSpeedY;
  }

  // Verificação de colisão com as raquetes
  if (
    (ballX <= player1.offsetWidth &&
      ballY + ball.offsetHeight >= player1Y &&
      ballY <= player1Y + player1.offsetHeight) ||
    (ballX >= containerWidth - player2.offsetWidth - ball.offsetWidth &&
      ballY + ball.offsetHeight >= player2Y &&
      ballY <= player2Y + player2.offsetHeight)
  ) {
    ballSpeedX = -ballSpeedX;
  }

  // Verificação de pontuação e reinício do jogo
  if (ballX <= 0 || ballX >= containerWidth - ball.offsetWidth) {
    ballX = containerWidth / 2;
    ballY = containerHeight / 2;
    ballSpeedX = -ballSpeedX;
  }

  // Movimento da IA (player2)
  // Implementação da lógica simples da IA aqui
  let player2Speed = 5;
  let paddleCenter = player2Y + paddles[1].offsetHeight / 2;
  if (paddleCenter < ballY - 35) {
    player2Y += player2Speed;
  } else if (paddleCenter > ballY + 35) {
    player2Y -= player2Speed;
  }

  // Atualização das posições das raquetes
  player1.style.top = player1Y + 'px';
  player2.style.top = player2Y + 'px';

  // Atualização da posição da bola
  ball.style.left = ballX + 'px';
  ball.style.top = ballY + 'px';

  requestAnimationFrame(update);
}

// Event listener para movimento do jogador (player1)
document.addEventListener('mousemove', function (e) {
  player1Y = e.clientY - paddles[0].offsetHeight / 2;
  if (player1Y >= containerHeight - paddles[0].offsetHeight) {
    player1Y = containerHeight - paddles[0].offsetHeight;
  }
  if (player1Y <= 0) {
    player1Y = 0;
  }
});
// Função para atualizar as cores com base nos controles
function updateColors() {
    const paddleColor = document.getElementById('paddleColor').value;
    const ballColor = document.getElementById('ballColor').value;
    const backgroundColor = document.getElementById('backgroundColor').value;
  
    paddles.forEach(paddle => {
      paddle.style.backgroundColor = paddleColor;
    });
  
    ball.style.backgroundColor = ballColor;
    container.style.backgroundColor = backgroundColor;
  }
  
  // Adicionar evento de mudança nos inputs de cor
  controls.addEventListener('change', updateColors);
  
  // Iniciar o jogo com cores padrão
  updateColors();
// Iniciar o jogo
update();
