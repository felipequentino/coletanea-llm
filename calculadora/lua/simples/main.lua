-- Calculadora Simples em Lua usando Love2D

function love.load()
    -- Definindo variáveis
    num1 = ""
    num2 = ""
    operador = ""
    resultado = ""
end

function love.draw()
    -- Desenhando os elementos na tela
    love.graphics.print("Calculadora Simples", 10, 10)
    love.graphics.print("Número 1: " .. num1, 10, 40)
    love.graphics.print("Operador: " .. operador, 10, 70)
    love.graphics.print("Número 2: " .. num2, 10, 100)
    love.graphics.print("Resultado: " .. resultado, 10, 130)
end

function love.keypressed(key)
    -- Verificando teclas pressionadas
    if key >= "0" and key <= "9" then
        -- Adicionando números
        if operador == "" then
            num1 = num1 .. key
        else
            num2 = num2 .. key
        end
    elseif key == "+" or key == "-" or key == "*" or key == "/" then
        -- Definindo operador
        operador = key
    elseif key == "return" then
        -- Calculando resultado
        calcularResultado()
    elseif key == "c" then
        -- Limpar tudo
        num1 = ""
        num2 = ""
        operador = ""
        resultado = ""
    end
end

function calcularResultado()
    -- Convertendo números de string para números
    local n1 = tonumber(num1) or 0
    local n2 = tonumber(num2) or 0

    -- Realizando a operação
    if operador == "+" then
        resultado = n1 + n2
    elseif operador == "-" then
        resultado = n1 - n2
    elseif operador == "*" then
        resultado = n1 * n2
    elseif operador == "/" then
        if n2 ~= 0 then
            resultado = n1 / n2
        else
            resultado = "Erro: Divisão por zero"
        end
    end
end
