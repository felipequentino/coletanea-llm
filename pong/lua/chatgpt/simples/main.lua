-- Variáveis para a bola
local ballX, ballY = 400, 300
local ballSpeedX, ballSpeedY = 200, 150
local ballRadius = 10

-- Variáveis para os paddles
local paddleWidth, paddleHeight = 10, 80
local leftPaddleX, leftPaddleY = 50, 260
local rightPaddleX, rightPaddleY = 740, 260
local paddleSpeed = 300

function love.load()
    love.window.setTitle("Pong")
    love.window.setMode(800, 600, {resizable=false})
end

function love.update(dt)
    -- Movimento dos paddles
    if love.keyboard.isDown("w") and leftPaddleY > 0 then
        leftPaddleY = leftPaddleY - paddleSpeed * dt
    elseif love.keyboard.isDown("s") and leftPaddleY < love.graphics.getHeight() - paddleHeight then
        leftPaddleY = leftPaddleY + paddleSpeed * dt
    end

    if love.keyboard.isDown("up") and rightPaddleY > 0 then
        rightPaddleY = rightPaddleY - paddleSpeed * dt
    elseif love.keyboard.isDown("down") and rightPaddleY < love.graphics.getHeight() - paddleHeight then
        rightPaddleY = rightPaddleY + paddleSpeed * dt
    end

    -- Movimento da bola
    ballX = ballX + ballSpeedX * dt
    ballY = ballY + ballSpeedY * dt

    -- Colisões com as paredes
    if ballY - ballRadius < 0 or ballY + ballRadius > love.graphics.getHeight() then
        ballSpeedY = -ballSpeedY
    end

    -- Colisões com os paddles
    if ballX - ballRadius < leftPaddleX + paddleWidth and ballY > leftPaddleY and ballY < leftPaddleY + paddleHeight then
        ballSpeedX = -ballSpeedX
    end

    if ballX + ballRadius > rightPaddleX and ballY > rightPaddleY and ballY < rightPaddleY + paddleHeight then
        ballSpeedX = -ballSpeedX
    end

    -- Verificações de pontuação
    if ballX - ballRadius < 0 then
        ballX, ballY = 400, 300
    elseif ballX + ballRadius > love.graphics.getWidth() then
        ballX, ballY = 400, 300
    end
end

function love.draw()
    -- Desenhar paddles
    love.graphics.rectangle("fill", leftPaddleX, leftPaddleY, paddleWidth, paddleHeight)
    love.graphics.rectangle("fill", rightPaddleX, rightPaddleY, paddleWidth, paddleHeight)

    -- Desenhar a bola
    love.graphics.circle("fill", ballX, ballY, ballRadius)
end
