-- Variáveis de configuração
local windowWidth = 800
local windowHeight = 600
local paddleWidth = 10
local paddleHeight = 80
local ballSize = 10
local paddleSpeed = 400
local ballSpeed = 300
local ballAcceleration = 1.05

local player1 = { x = 50, y = windowHeight / 2 - paddleHeight / 2, score = 0 }
local player2 = { x = windowWidth - 50 - paddleWidth, y = windowHeight / 2 - paddleHeight / 2, score = 0 }
local ball = { x = windowWidth / 2 - ballSize / 2, y = windowHeight / 2 - ballSize / 2, dx = ballSpeed, dy = ballSpeed }

local backgroundColor = { 0.1, 0.1, 0.1 } -- Cor do plano de fundo em RGB
local player1Color = { 0.8, 0.2, 0.2 } -- Cor da raquete do jogador 1 em RGB
local player2Color = { 0.2, 0.2, 0.8 } -- Cor da raquete do jogador 2 (IA) em RGB
local ballColor = { 0.9, 0.9, 0.9 } -- Cor da bola em RGB

function love.load()
    love.window.setTitle("Pong AI")
    love.window.setMode(windowWidth, windowHeight)
end

function love.update(dt)
    -- Controle do jogador
    if love.keyboard.isDown("w") and player1.y > 0 then
        player1.y = player1.y - paddleSpeed * dt
    elseif love.keyboard.isDown("s") and player1.y < windowHeight - paddleHeight then
        player1.y = player1.y + paddleSpeed * dt
    end

    -- Controle da IA
    -- Previsão de trajetória da bola para a raquete da IA
    local predictedPosY = ball.y + (ball.dy * (player2.x - ball.x) / ball.dx)
    if predictedPosY < player2.y + paddleHeight / 2 then
        player2.y = player2.y - paddleSpeed * dt
    elseif predictedPosY > player2.y + paddleHeight / 2 then
        player2.y = player2.y + paddleSpeed * dt
    end


    -- Movimentação da bola
    ball.x = ball.x + ball.dx * dt
    ball.y = ball.y + ball.dy * dt

    -- Colisões com as paredes
    if ball.y <= 0 or ball.y >= windowHeight - ballSize then
        ball.dy = -ball.dy
    end

    -- Verificação de colisão com as raquetes
    if ball.x < player1.x + paddleWidth and ball.y + ballSize > player1.y and ball.y < player1.y + paddleHeight then
        ball.dx = math.abs(ball.dx)
        ball.dx = ball.dx * ballAcceleration
    elseif ball.x + ballSize > player2.x and ball.y + ballSize > player2.y and ball.y < player2.y + paddleHeight then
        ball.dx = -math.abs(ball.dx)
        ball.dx = ball.dx * ballAcceleration
    end

    -- Verificação de pontuação
    if ball.x < 0 then
        player2.score = player2.score + 1
        ball.x = windowWidth / 2 - ballSize / 2
        ball.y = windowHeight / 2 - ballSize / 2
        ball.dx = ballSpeed
        ball.dy = ballSpeed
    elseif ball.x > windowWidth then
        player1.score = player1.score + 1
        ball.x = windowWidth / 2 - ballSize / 2
        ball.y = windowHeight / 2 - ballSize / 2
        ball.dx = -ballSpeed
        ball.dy = ballSpeed
    end
end

function love.draw()
    -- Definição da cor de fundo
    love.graphics.setBackgroundColor(backgroundColor)

    -- Desenhar raquetes, bola e placar com as cores personalizadas
    love.graphics.setColor(player1Color)
    love.graphics.rectangle("fill", player1.x, player1.y, paddleWidth, paddleHeight)

    love.graphics.setColor(player2Color)
    love.graphics.rectangle("fill", player2.x, player2.y, paddleWidth, paddleHeight)

    love.graphics.setColor(ballColor)
    love.graphics.rectangle("fill", ball.x, ball.y, ballSize, ballSize)

    -- Desenhar o placar
    love.graphics.setColor(1, 1, 1) -- Definir a cor do texto como branca
    love.graphics.print("Player 1: " .. player1.score, windowWidth / 4, 10)
    love.graphics.print("Player 2: " .. player2.score, windowWidth * 3 / 4, 10)
end
