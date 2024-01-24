require("iuplua")

-- Função para avaliar a expressão matemática
function evaluateExpression(expression)
    local chunk, errorMsg = loadstring("return " .. expression)
    if chunk then
        local result = chunk()
        return result
    else
        return "Erro na expressão: " .. errorMsg
    end
end

-- Função chamada ao pressionar um botão
function buttonAction(buttonValue)
    if buttonValue == "=" then
        local result = evaluateExpression(textbox.value)
        textbox.value = tostring(result)
    else
        textbox.value = textbox.value .. buttonValue
    end
end

-- Criar elementos da GUI
textbox = iup.text { value = "", expand = "HORIZONTAL" }

buttons = {
    {"7", "8", "9", "/"},
    {"4", "5", "6", "*"},
    {"1", "2", "3", "-"},
    {"0", ".", "=", "+"}
}

grid = iup.gridbox {
    iup.fill {}, iup.fill {}, iup.fill {},
    iup.fill {},
    iup.fill {}, iup.fill {}, iup.fill {},
    iup.fill {},
    iup.fill {}, iup.fill {}, iup.fill {},
    iup.fill {},
    iup.fill {}, iup.fill {}, iup.fill {},
    iup.fill {},
    iup.fill {},
    numdiv = 4,
    horizontalgap = 5,
    verticalgap = 5,
}

-- Adicionar botões à grade
for i, row in ipairs(buttons) do
    for j, value in ipairs(row) do
        local button = iup.button {
            title = value,
            action = function() buttonAction(value) end
        }
        grid["cell" .. (i - 1) .. ":" .. (j - 1)] = button
    end
end

-- Criar a janela principal
dlg = iup.dialog {
    iup.vbox {
        textbox,
        grid
    },
    title = "Calculadora",
    size = "QUARTERxQUARTER",
}

-- Mostrar a janela
dlg:show()

-- Iniciar a execução da interface gráfica
iup.MainLoop()
