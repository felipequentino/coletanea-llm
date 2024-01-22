const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const player = {
  x: 250,
  y: 200,
  speed: 10,
};

const cpu = {
  x: 250,
  y: 200,
  speed: 10,
};

const ball = {
  x: 250,
  y: 250,
  vx: 5,
  vy: 5,
};

function update() {
  // Movimenta a bola
  ball.x += ball.vx;
  ball.y += ball.vy;

  // Verifica se a bola saiu da tela
  if (ball.x < 0 || ball.x > canvas.width) {
    ball.vx *= -1;
  }
  if (ball.y < 0 || ball.y > canvas.height) {
    ball.vy *= -1;
  }

  // Verifica se a bola bateu na raquete do jogador
  if (ball.x >= player.x && ball.x <= player.x + player.width &&
    ball.y >= player.y && ball.y <= player.y + player.height) {
    ball.vx *= -1;
  }

  // Verifica se a bola bateu na raquete do computador
  if (ball.x >= cpu.x && ball.x <= cpu.x + cpu.width &&
    ball.y >= cpu.y && ball.y <= cpu.y + cpu.height) {
    ball.vx *= -1;
  }

  // Movimenta a raquete do jogador
  if (window.event.keyCode === 38) {
    player.y -= player.speed;
  } else if (window.event.keyCode === 40) {
    player.y += player.speed;
  }

  // Movimenta a raquete do computador
  cpu.y = ball.y;

  // Reinicia o jogo se a bola passou da linha de fundo
  if (ball.y < 0) {
    player.score++;
    ball.x = 250;
    ball.y = 250;
    ball.vx = 5;
    ball.vy = 5;
  } else if (ball.y > canvas.height) {
    cpu.score++;
    ball.x = 250;
    ball.y = 250;
    ball.vx = 5;
    ball.vy = 5;
  }

  // Atualiza a tela
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = "black";
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = "red";
  ctx.fillRect(player.x, player.y, player.width, player.height);
  ctx.fillStyle = "blue";
  ctx.fillRect(cpu.x, cpu.y, cpu.width, cpu.height);
  ctx.fillStyle = "white";
  ctx.fillRect(ball.x, ball.y, ball.width, ball.height);
} 

update();