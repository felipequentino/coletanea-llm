let currentInput = '';
let currentOperation = null;
let storedInput = null;

function appendToDisplay(value) {
    currentInput += value;
    updateDisplay();
}

function setOperation(operation) {
    if (currentOperation !== null) {
        calculateResult();
    }
    currentOperation = operation;
    storedInput = currentInput;
    currentInput = '';
}

function calculateResult() {
    if (currentOperation === null || storedInput === null) {
        return;
    }

    let result;

    switch (currentOperation) {
        case '+':
            result = parseFloat(storedInput) + parseFloat(currentInput);
            break;
        case '-':
            result = parseFloat(storedInput) - parseFloat(currentInput);
            break;
        case '*':
            result = parseFloat(storedInput) * parseFloat(currentInput);
            break;
        case '/':
            result = parseFloat(storedInput) / parseFloat(currentInput);
            break;
    }

    currentInput = result.toString();
    currentOperation = null;
    storedInput = null;
    updateDisplay();
}

function clearDisplay() {
    currentInput = '';
    currentOperation = null;
    storedInput = null;
    updateDisplay();
}

function updateDisplay() {
    document.getElementById('display').value = currentInput;
}
