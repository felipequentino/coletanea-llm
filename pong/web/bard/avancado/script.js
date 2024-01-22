// Variáveis globais
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
const largura = canvas.width;
const altura = canvas.height;

class Raquete {
  constructor(x, y, velocidade) {
    this.x = x;
    this.y = y;
    this.velocidade = velocidade;
    this.cor = "red";
  }
}

class AI {
  constructor(raquete) {
    this.raquete = raquete;
    this.modeloPrevisora = new RegressaoLinear();
    this.geradorAleatorio = new Random();
    this.cor = "blue";
  }
}
class Bola {
    constructor(x, y) {
      this.x = x;
      this.y = y;
      this.direcaoX = 1;
      this.velocidadeX = 1;
      this.velocidadeY = 1;
      this.cor = "white";
    }
  }

class Background {
  constructor() {
    this.imagem = "background.jpg";
  }

  render() {
    // Renderiza a imagem do plano de fundo
    ctx.drawImage(this.imagem, 0, 0);
  }
}


function onButtonClick(event) {
    if (event.target.id === "cor-raquete-1") {
      // Abre um diálogo para selecionar a cor da raquete 1
      const cor = prompt("Selecione a cor da raquete 1:");
      raquete1.cor = cor;
    } else if (event.target.id === "cor-raquete-2") {
      // Abre um diálogo para selecionar a cor da raquete 2
      const cor = prompt("Selecione a cor da raquete 2:");
      raquete2.cor = cor;
    }
  }
function onButtonClick(event) {
  if (event.target.id === "cor-bola") {
    // Abre um diálogo para selecionar a cor da bola
    const cor = prompt("Selecione a cor da bola:");
    bola.cor = cor;
  }
}
function onButtonClick(event) {
    if (event.target.id === "imagem-plano-de-fundo") {
      // Abre um diálogo para selecionar a imagem do plano de fundo
      const imagem = prompt("Selecione a imagem do plano de fundo:");
      background.imagem = imagem;
    }
  }
  
// Objetos das raquetes
const raquete1 = new Raquete(100, altura / 2);
const raquete2 = new Raquete(largura - 100, altura / 2);

// Objeto da bola
const bola = new Bola(largura / 2, altura / 2);

// Objeto do plano de fundo
const background = new Background();

// Função de inicialização
function init() {
  // Inicializa a IA da raquete 2
  raquete2.ai = new AI(raquete2);

  // Inicializa o jogo
  startGame();
}

function atualizar() {
    // Atualiza a posição da bola
    bola.atualizar();
  
    // Verifica se a bola passou da linha
    if (bola.x < 0 || bola.x > largura) {
      if (bola.x < 0) {
        // A raquete 1 marcou um ponto
        raquete1.pontos++;
      } else {
        // A raquete 2 marcou um ponto
        raquete2.pontos++;
      }
  
      // Reinicia a bola
      bola.x = largura / 2;
      bola.y = altura / 2;
  
      // Alterna o jogador que serve
      if (raquete1.serve) {
        raquete1.serve = false;
        raquete2.serve = true;
      } else {
        raquete1.serve = true;
        raquete2.serve = false;
      }
    }
  
    // Verifica se a bola colidiu com alguma raquete
    if (bola.colisao(raquete1) || bola.colisao(raquete2)) {
      // Altera a direção da bola
      bola.direcaoX = -bola.direcaoX;
  
      // Aumenta a velocidade da bola
      bola.velocidadeX += 0.1;
      bola.velocidadeY += 0.1;
  
      // Aplica amortecimento ao movimento das raquetes
      raquete1.x += raquete1.velocidadeX * 0.8;
      raquete1.y += raquete1.velocidadeY * 0.8;
      raquete2.x += raquete2.velocidadeX * 0.8;
      raquete2.y += raquete2.velocidadeY * 0.8;
    }
  
    // Atualiza a posição das raquetes
    raquete1.atualizar();
    raquete2.atualizar();
  
    // Renderiza o jogo
    render();
  }

// Função de atualização
function update() {
  // Atualiza a posição da bola
  bola.atualizar();

  // Verifica se a bola passou da linha
  if (bola.x < 0 || bola.x > largura) {
    if (bola.x < 0) {
      // A raquete 1 marcou um ponto
      raquete1.pontos++;
    } else {
      // A raquete 2 marcou um ponto
      raquete2.pontos++;
    }

    // Reinicia a bola
    bola.x = largura / 2;
    bola.y = altura / 2;

    // Alterna o jogador que serve
    if (raquete1.serve) {
      raquete1.serve = false;
      raquete2.serve = true;
    } else {
      raquete1.serve = true;
      raquete2.serve = false;
    }
  }

  // Verifica se a bola colidiu com alguma raquete
  if (bola.colisao(raquete1) || bola.colisao(raquete2)) {
    // Altera a direção da bola
    bola.direcaoX = -bola.direcaoX;

    // Aumenta a velocidade da bola
    bola.velocidadeX += 0.1;
    bola.velocidadeY += 0.1;
  }

  // Atualiza a posição das raquetes
  raquete1.atualizar();
  raquete2.atualizar();

  // Renderiza o jogo
  render();
}

// Função de renderização
function render() {
  // Limpa o canvas
  ctx.clearRect(0, 0, largura, altura);

  // Renderiza o plano de fundo
  background.render();

  // Renderiza as raquetes
  raquete1.render();
  raquete2.render();

  // Renderiza a bola
  bola.render();
}

// Função de controle da raquete 1
function onKeyDown(event) {
  if (event.keyCode === 38) {
    // Movimenta a raquete para cima
    raquete1.y -= 50;
  } else if (event.keyCode === 40) {
    // Movimenta a raquete para baixo
    raquete1.y += 50;
  }
}

// Função de inicialização do jogo
function startGame() {
  // Define a raquete 1 como servidora
  raquete1.serve = true;
}
