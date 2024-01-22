-- Definindo as variáveis iniciais
local ball = { x = 400, y = 300, radius = 10, speedX = 200, speedY = 200 }
local player = { x = 50, y = 250, width = 10, height = 80, speed = 400 }
local enemy = { x = 740, y = 250, width = 10, height = 80, speed = 400 }
local scorePlayer = 0
local scoreEnemy = 0

function love.load()
    love.window.setTitle("Pong Game")
    love.window.setMode(800, 600, {resizable=false})
end

function love.update(dt)
    -- Controles do jogador
    if love.keyboard.isDown("w") and player.y > 0 then
        player.y = player.y - player.speed * dt
    elseif love.keyboard.isDown("s") and player.y < love.graphics.getHeight() - player.height then
        player.y = player.y + player.speed * dt
    end

    -- Movimento da raquete inimiga (IA simples)
    if ball.y < enemy.y + enemy.height / 2 then
        enemy.y = enemy.y - enemy.speed * dt
    elseif ball.y > enemy.y + enemy.height / 2 then
        enemy.y = enemy.y + enemy.speed * dt
    end

    -- Movimento da bola
    ball.x = ball.x + ball.speedX * dt
    ball.y = ball.y + ball.speedY * dt

    -- Colisão da bola com as paredes superior e inferior
    if ball.y - ball.radius < 0 or ball.y + ball.radius > love.graphics.getHeight() then
        ball.speedY = -ball.speedY
    end

    -- Colisão da bola com as raquetes
    if ball.x - ball.radius < player.x + player.width and ball.y > player.y and ball.y < player.y + player.height then
        ball.speedX = -ball.speedX
        ball.speedX = ball.speedX * 1.1  -- Aumenta a velocidade após rebatida
        ball.speedY = ball.speedY * 1.1  -- Aumenta a velocidade após rebatida
    elseif ball.x + ball.radius > enemy.x and ball.y > enemy.y and ball.y < enemy.y + enemy.height then
        ball.speedX = -ball.speedX
        ball.speedX = ball.speedX * 1.1  -- Aumenta a velocidade após rebatida
        ball.speedY = ball.speedY * 1.1  -- Aumenta a velocidade após rebatida
    end

    -- Verifica se a bola passou das raquetes
    if ball.x - ball.radius < 0 then
        scoreEnemy = scoreEnemy + 1
        resetBall()
    elseif ball.x + ball.radius > love.graphics.getWidth() then
        scorePlayer = scorePlayer + 1
        resetBall()
    end
end

function love.draw()
    -- Desenha as raquetes e a bola
    love.graphics.rectangle("fill", player.x, player.y, player.width, player.height)
    love.graphics.rectangle("fill", enemy.x, enemy.y, enemy.width, enemy.height)
    love.graphics.circle("fill", ball.x, ball.y, ball.radius)

    -- Exibe a pontuação
    love.graphics.print("Player: " .. scorePlayer, 50, 20)
    love.graphics.print("Enemy: " .. scoreEnemy, 650, 20)
end

function resetBall()
    ball.x = love.graphics.getWidth() / 2
    ball.y = love.graphics.getHeight() / 2
    ball.speedX = 200
    ball.speedY = 200
end
