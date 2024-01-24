import tkinter as tk
import math

class Calculator:
    def __init__(self, master):
        self.master = master
        master.title("Calculadora Avançada")

        # Entrada
        self.entry = tk.Entry(master, width=20, font=('Arial', 16), bd=5, relief=tk.GROOVE)
        self.entry.grid(row=0, column=0, columnspan=6)

        # Botões
        buttons = [
            ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('/', 1, 3),
            ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('*', 2, 3),
            ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('-', 3, 3),
            ('0', 4, 0), ('.', 4, 1), ('=', 4, 2), ('+', 4, 3),
            ('sin', 5, 0), ('cos', 5, 1), ('tan', 5, 2), ('^', 5, 3),
            ('sqrt', 6, 0), ('log', 6, 1), ('!', 6, 2), ('C', 6, 3),
        ]

        for (text, row, col) in buttons:
            button = tk.Button(master, text=text, command=lambda t=text: self.button_click(t),
                               width=5, height=2, font=('Arial', 14), bd=5, relief=tk.GROOVE)
            button.grid(row=row, column=col)

    def button_click(self, value):
        if value == '=':
            result = self.calculate()
            self.entry.delete(0, tk.END)
            self.entry.insert(tk.END, str(result))
        elif value == 'C':
            self.entry.delete(0, tk.END)
        else:
            current_text = self.entry.get()
            self.entry.delete(0, tk.END)
            self.entry.insert(tk.END, current_text + value)

    def calculate(self):
        expression = self.entry.get()

        try:
            result = self.evaluate_expression(expression)
            return result
        except Exception as e:
            return 'Erro'

    def evaluate_expression(self, expression):
        tokens = expression.split()

        for i, token in enumerate(tokens):
            if token == 'sin':
                tokens[i] = str(self.sin(float(tokens[i + 1])))
                tokens.pop(i + 1)
            elif token == 'cos':
                tokens[i] = str(self.cos(float(tokens[i + 1])))
                tokens.pop(i + 1)
            elif token == 'tan':
                tokens[i] = str(self.tan(float(tokens[i + 1])))
                tokens.pop(i + 1)
            elif token == '^':
                tokens[i] = '**'
            elif token == 'sqrt':
                tokens[i] = str(self.sqrt(float(tokens[i + 1])))
                tokens.pop(i + 1)
            elif token == 'log':
                tokens[i] = str(self.log(float(tokens[i + 1])))
                tokens.pop(i + 1)
            elif token == '!':
                tokens[i] = str(self.factorial(int(tokens[i - 1])))
                tokens.pop(i - 1)

        return self.safe_eval(' '.join(tokens))

    def safe_eval(self, expr):
        try:
            return eval(expr, {"__builtins__": None}, {"math": math})
        except Exception as e:
            return 'Erro'

    def sin(self, value):
        return math.sin(math.radians(value))

    def cos(self, value):
        return math.cos(math.radians(value))

    def tan(self, value):
        return math.tan(math.radians(value))

    def sqrt(self, value):
        return math.sqrt(value)

    def log(self, value):
        return math.log10(value)

    def factorial(self, value):
        return math.factorial(value)

def main():
    root = tk.Tk()
    calculator = Calculator(root)
    root.mainloop()

if __name__ == "__main__":
    main()
