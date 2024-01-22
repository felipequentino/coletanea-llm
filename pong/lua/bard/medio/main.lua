-- Importações
local love = require("love")

-- Constantes
local LARGURA_TELA = 640
local ALTURA_TELA = 480
local VELOCIDADE_INICIAL = 100

-- Variáveis globais
local bola = {
  x = LARGURA_TELA / 2,
  y = ALTURA_TELA / 2,
  vx = VELOCIDADE_INICIAL,
  vy = VELOCIDADE_INICIAL
}
local jogador1 = {
  x = 0,
  y = ALTURA_TELA / 2
}
local jogador2 = {
  x = LARGURA_TELA,
  y = ALTURA_TELA / 2
}
local ia = {
  x = LARGURA_TELA / 2,
  y = ALTURA_TELA / 2
}

-- Funções
function love.load()
  love.graphics.setBackgroundColor(255, 255, 255)
end

function love.update(dt)
  -- Atualizar a posição da bola
  bola.x = bola.x + bola.vx * dt
  bola.y = bola.y + bola.vy * dt

  -- Verificar colisões
  if bola.y < 0 then
    bola.vy = -bola.vy
  end
  if bola.y > ALTURA_TELA then
    bola.vy = -bola.vy
  end
  if bola.x < jogador1.x + jogador1.largura then
    if bola.y > jogador1.y - jogador1.altura / 2 and bola.y < jogador1.y + jogador1.altura / 2 then
      bola.vx = -bola.vx
    else
      -- Ponto para o jogador 2
    end
  end
  if bola.x > jogador2.x - jogador2.largura then
    if bola.y > jogador2.y - jogador2.altura / 2 and bola.y < jogador2.y + jogador2.altura / 2 then
      bola.vx = -bola.vx
    else
      -- Ponto para o jogador 1
    end
  end

  -- Atualizar a posição da IA
  ia.x = bola.x

  -- Aumentar a velocidade da bola
  bola.vx = bola.vx + 1
  bola.vy = bola.vy + 1
end

function love.draw()
  -- Desenhar a bola
  love.graphics.rectangle("fill", bola.x, bola.y, 20, 20)

  -- Desenhar a raquete do jogador 1
  love.graphics.rectangle("fill", jogador1.x, jogador1.y, 20, 100)

  -- Desenhar a raquete do jogador 2
  love.graphics.rectangle("fill", jogador2.x, jogador2.y, 20, 100)

  -- Desenhar a raquete da IA
  love.graphics.rectangle("fill", ia.x, ia.y, 20, 100)
end

function love.keypressed(key)
  if key == "w" then
    jogador1.y = jogador1.y - 5
  end
  if key == "s" then
    jogador1.y = jogador1.y + 5
  end
end
