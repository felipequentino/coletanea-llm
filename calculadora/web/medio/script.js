let display = document.getElementById('display');
let memory = 0;

function appendToDisplay(value) {
    display.value += value;
}

function calculateResult() {
    try {
        display.value = eval(display.value);
    } catch (error) {
        display.value = 'Error';
    }
}

function clearDisplay() {
    display.value = '';
}

function memoryStore() {
    memory = parseFloat(display.value);
}

function memoryRecall() {
    display.value += memory;
}

function memoryAdd() {
    memory += parseFloat(display.value);
}

function memorySubtract() {
    memory -= parseFloat(display.value);
}
