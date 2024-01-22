-- Importa o framework LÖVE
require("love")

-- Declaração de variáveis globais
local largura = 800
local altura = 600
local velocidade = 5
local jogador1, jogador2
local bola

-- Função de inicialização do jogo
function love.load()
  -- Inicializa o framework LÖVE
  love.graphics.setMode(largura, altura)

  -- Cria as raquetes
  jogador1 = love.graphics.newRectangle(0, altura / 2 - 50, 100, 100)
  jogador2 = love.graphics.newRectangle(largura, altura / 2 - 50, 100, 100)

  -- Cria a bola
  bola = love.graphics.newCircle(largura / 2, altura / 2, 25)
end

-- Função de atualização do jogo
function love.update(dt)
  -- Move as raquetes
  jogador1:move(dt * velocidade * love.keyboard.isDown("w") - dt * velocidade * love.keyboard.isDown("s"))
  jogador2:move(dt * velocidade * love.keyboard.isDown("up") - dt * velocidade * love.keyboard.isDown("down"))

  -- Move a bola
  bola:move(dt * velocidade)

  -- Verifica colisões
  if bola:collide(jogador1) then
    bola:reflect("x")
  end

  if bola:collide(jogador2) then
    bola:reflect("x")
  end

  -- Verifica se a bola saiu da tela
  if bola.x < 0 or bola.x > largura then
    love.event.quit()
  end
end

-- Função de renderização do jogo
function love.draw()
  -- Desenha o fundo
  love.graphics.setColor(255, 255, 255)
  love.graphics.rectangle("fill", 0, 0, largura, altura)

  -- Desenha as raquetes
  love.graphics.setColor(0, 0, 255)
  love.graphics.draw(jogador1)
  love.graphics.setColor(255, 0, 0)
  love.graphics.draw(jogador2)

  -- Desenha a bola
  love.graphics.setColor(255, 255, 0)
  love.graphics.draw(bola)
end
