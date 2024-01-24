-- Inicializa o Love2D
function love.load()
    -- Variáveis
    input = ""
    result = ""
    memory = 0

    -- Configuração da fonte
    font = love.graphics.newFont(24)

    -- Configuração dos botões
    buttons = {
        {label = "7", x = 50, y = 200, width = 50, height = 50},
        {label = "8", x = 110, y = 200, width = 50, height = 50},
        {label = "9", x = 170, y = 200, width = 50, height = 50},
        {label = "/", x = 230, y = 200, width = 50, height = 50},

        {label = "4", x = 50, y = 260, width = 50, height = 50},
        {label = "5", x = 110, y = 260, width = 50, height = 50},
        {label = "6", x = 170, y = 260, width = 50, height = 50},
        {label = "*", x = 230, y = 260, width = 50, height = 50},

        {label = "1", x = 50, y = 320, width = 50, height = 50},
        {label = "2", x = 110, y = 320, width = 50, height = 50},
        {label = "3", x = 170, y = 320, width = 50, height = 50},
        {label = "-", x = 230, y = 320, width = 50, height = 50},

        {label = "0", x = 50, y = 380, width = 50, height = 50},
        {label = ".", x = 110, y = 380, width = 50, height = 50},
        {label = "=", x = 170, y = 380, width = 50, height = 50},
        {label = "+", x = 230, y = 380, width = 50, height = 50},

        {label = "C", x = 50, y = 440, width = 110, height = 50},
        {label = "M", x = 170, y = 440, width = 110, height = 50},
    }
end

-- Atualiza a tela
function love.draw()
    love.graphics.setFont(font)

    -- Desenha a entrada e o resultado
    love.graphics.printf(input, 50, 50, love.graphics.getWidth() - 100, "right")
    love.graphics.printf(result, 50, 100, love.graphics.getWidth() - 100, "right")

    -- Desenha os botões
    for _, button in ipairs(buttons) do
        love.graphics.rectangle("line", button.x, button.y, button.width, button.height)
        love.graphics.printf(button.label, button.x, button.y + button.height / 2 - 12, button.width, "center")
    end
end

-- Lida com o clique do mouse
function love.mousepressed(x, y, button, istouch, presses)
    for _, btn in ipairs(buttons) do
        if x >= btn.x and x <= btn.x + btn.width and y >= btn.y and y <= btn.y + btn.height then
            handleButtonClick(btn.label)
        end
    end
end

-- Lida com os eventos do teclado
function love.keypressed(key)
    if key == "return" then
        calculateResult()
    elseif key == "c" then
        input = ""
        result = ""
    elseif key == "m" then
        memory = tonumber(result) or 0
    elseif key == "r" then
        input = input .. memory
    else
        handleButtonClick(key)
    end
end

-- Lida com o clique dos botões
function handleButtonClick(label)
    if tonumber(label) ~= nil or label == "." then
        input = input .. label
    elseif label == "=" then
        calculateResult()
    elseif label == "C" then
        input = ""
        result = ""
    elseif label == "M" then
        memory = tonumber(result) or 0
    else
        input = input .. " " .. label .. " "
    end
end

-- Calcula o resultado
function calculateResult()
    local expression = load("return " .. input)
    local success, value = pcall(expression)

    if success then
        result = tostring(value)
    else
        result = "Erro"
    end
end
