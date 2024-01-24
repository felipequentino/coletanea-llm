import tkinter as tk

class Calculadora:
    def __init__(self, root):
        self.root = root
        self.root.title("Calculadora")

        # Variável para armazenar a expressão
        self.expression = tk.StringVar()

        # Entrada para exibir a expressão
        entry = tk.Entry(root, textvariable=self.expression, font=('Arial', 18), justify='right')
        entry.grid(row=0, column=0, columnspan=4)

        # Botões
        buttons = [
            '7', '8', '9', '/',
            '4', '5', '6', '*',
            '1', '2', '3', '-',
            '0', 'C', '=', '+'
        ]

        row_val = 1
        col_val = 0

        for button in buttons:
            tk.Button(root, text=button, padx=20, pady=20, font=('Arial', 14), command=lambda btn=button: self.button_click(btn)).grid(row=row_val, column=col_val)
            col_val += 1
            if col_val > 3:
                col_val = 0
                row_val += 1

    def button_click(self, button):
        if button == '=':
            try:
                # Avaliar a expressão e exibir o resultado
                result = str(eval(self.expression.get()))
                self.expression.set(result)
            except Exception as e:
                self.expression.set("Erro")
        elif button == 'C':
            # Limpar a entrada
            self.expression.set('')
        else:
            # Adicionar o botão pressionado à expressão
            current_expression = self.expression.get()
            new_expression = current_expression + button
            self.expression.set(new_expression)

if __name__ == "__main__":
    root = tk.Tk()
    app = Calculadora(root)
    root.mainloop()
