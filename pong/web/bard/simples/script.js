// Variáveis globais
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
const bola = {
  x: 250,
  y: 250,
  vx: 5,
  vy: 5,
};
const barra1 = {
  x: 100,
  y: 200,
  h: 50,
};
const barra2 = {
  x: 400,
  y: 200,
  h: 50,
};

// Inicializa o jogo
function init() {
  bola.x = canvas.width / 2;
  bola.y = canvas.height / 2;
}

// Desenha o jogo
function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // Desenha a bola
  ctx.fillStyle = "red";
  ctx.fillRect(bola.x, bola.y, 20, 20);

  // Desenha a barra 1
  ctx.fillStyle = "blue";
  ctx.fillRect(barra1.x, barra1.y, barra1.h, 20);

  // Desenha a barra 2
  ctx.fillStyle = "green";
  ctx.fillRect(barra2.x, barra2.y, barra2.h, 20);
}

// Atualiza o jogo
function update() {
  // Move a bola
  bola.x += bola.vx;
  bola.y += bola.vy;

  // Verifica se a bola atingiu a borda superior ou inferior
  if (bola.y < 0 || bola.y > canvas.height) {
    bola.vy *= -1;
  }

  // Verifica se a bola atingiu uma das barras
  if (bola.x < barra1.x + barra1.h && bola.y > barra1.y && bola.y < barra1.y + 20) {
    bola.vx *= -1;
  } else if (bola.x > barra2.x - barra2.h && bola.y > barra2.y && bola.y < barra2.y + 20) {
    bola.vx *= -1;
  }

  // Atualiza a pontuação
  if (bola.x < 0) {
    console.log("Jogador 2 venceu!");
  } else if (bola.x > canvas.width) {
    console.log("Jogador 1 venceu!");
  }
}

// Eventos
window.addEventListener("keydown", function(event) {
  if (event.keyCode === 38) {
    barra1.y -= 10;
  } else if (event.keyCode === 40) {
    barra1.y += 10;
  }
});

// Inicia o jogo
init();
setInterval(update, 30);
draw();
