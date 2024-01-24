document.addEventListener("DOMContentLoaded", function () {
    const input = document.getElementById("input");
    const buttons = document.querySelector(".buttons");

    buttons.addEventListener("click", handleClick);

    function handleClick(e) {
        const target = e.target;

        if (target.tagName === "BUTTON") {
            const buttonText = target.textContent;
            handleButtonPress(buttonText);
        }
    }
    let currentInput = "";
    let result = null;

    function handleButtonPress(value) {
        switch (value) {
            case "=":
                calculateResult();
                break;
            case "C":
                clearInput();
                break;
            case "sin":
                handleTrigonometricFunction(Math.sin);
                break;
            case "cos":
                handleTrigonometricFunction(Math.cos);
                break;
            case "tan":
                handleTrigonometricFunction(Math.tan);
                break;
            case "^":
                handlePower();
                break;
            case "√":
                handleSquareRoot();
                break;
            case "log":
                handleLogarithm();
                break;
            case "!":
                handleFactorial();
                break;
            default:
                currentInput += value;
                break;
        }

        updateDisplay();
    }

    function updateDisplay() {
        input.value = currentInput;
    }

    function calculateResult() {
        try {
            currentInput = evaluateExpression(currentInput).toString();
            result = null;
        } catch (error) {
            currentInput = "Erro";
        }

        updateDisplay();
    }

    function clearInput() {
        currentInput = "";
        result = null;
        updateDisplay();
    }

    function evaluateExpression(expression) {
        try {
            return math.evaluate(expression);
        } catch (error) {
            throw new Error("Expressão inválida");
        }
    }

    function handleTrigonometricFunction(func) {
        try {
            const value = evaluateExpression(currentInput);
            currentInput = func(value).toString();
        } catch (error) {
            currentInput = "Erro";
        }
    }

    function handlePower() {
        const parts = currentInput.split("^");
        if (parts.length === 2) {
            const base = evaluateExpression(parts[0]);
            const exponent = evaluateExpression(parts[1]);
            currentInput = Math.pow(base, exponent).toString();
        } else {
            currentInput = "Erro";
        }
    }

    function handleSquareRoot() {
        try {
            const value = evaluateExpression(currentInput);
            currentInput = Math.sqrt(value).toString();
        } catch (error) {
            currentInput = "Erro";
        }
    }

    function handleLogarithm() {
        try {
            const value = evaluateExpression(currentInput);
            currentInput = Math.log10(value).toString();
        } catch (error) {
            currentInput = "Erro";
        }
    }

    function handleFactorial() {
        try {
            const value = evaluateExpression(currentInput);
            currentInput = factorial(value).toString();
        } catch (error) {
            currentInput = "Erro";
        }
    }

    function factorial(num) {
        if (num === 0 || num === 1) {
            return 1;
        } else {
            return num * factorial(num - 1);
        }
    }
});
