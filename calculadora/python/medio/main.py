import tkinter as tk
from tkinter import messagebox
import math
import json

class CalculadoraGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Calculadora")

        self.current_value = tk.StringVar()
        self.entry = tk.Entry(root, textvariable=self.current_value, font=('Arial', 14), justify='right')
        self.entry.grid(row=0, column=0, columnspan=5)

        buttons = [
            ('7', 1, 0), ('8', 1, 1), ('9', 1, 2), ('/', 1, 3),
            ('4', 2, 0), ('5', 2, 1), ('6', 2, 2), ('*', 2, 3),
            ('1', 3, 0), ('2', 3, 1), ('3', 3, 2), ('-', 3, 3),
            ('0', 4, 0), ('.', 4, 1), ('=', 4, 2), ('+', 4, 3),
            ('sin', 5, 0), ('cos', 5, 1), ('tan', 5, 2), ('^', 5, 3),
            ('sqrt', 6, 0), ('log', 6, 1), ('MR', 6, 2), ('C', 6, 3),
            ('Save', 7, 0), ('Load', 7, 1), ('Unit Conv', 7, 2)
        ]

        for (text, row, col) in buttons:
            tk.Button(root, text=text, command=lambda t=text: self.button_click(t)).grid(row=row, column=col)

        self.memory = 0

    def button_click(self, value):
        if value == '=':
            try:
                result = eval(self.current_value.get())
                self.current_value.set(result)
            except Exception as e:
                messagebox.showerror("Erro", f"Erro na expressão: {e}")
        elif value == 'C':
            self.current_value.set('')
        elif value == 'MR':
            self.current_value.set(self.memory)
        elif value == 'Save':
            self.save_memory()
        elif value == 'Load':
            self.load_memory()
        elif value == 'Unit Conv':
            self.unit_conversion()
        else:
            current_expression = self.current_value.get()
            current_expression += str(value)
            self.current_value.set(current_expression)

    def save_memory(self):
        try:
            self.memory = eval(self.current_value.get())
            messagebox.showinfo("Salvo", "Valor salvo com sucesso!")
        except Exception as e:
            messagebox.showerror("Erro", f"Erro ao salvar valor: {e}")

    def load_memory(self):
        self.current_value.set(str(self.memory))

    def unit_conversion(self):
        try:
            value = float(self.current_value.get())
            converted_value = value * 100  # Exemplo de conversão de metros para centímetros
            self.current_value.set(converted_value)
        except ValueError:
            messagebox.showerror("Erro", "Por favor, insira um valor numérico para a conversão.")

if __name__ == "__main__":
    root = tk.Tk()
    calculator = CalculadoraGUI(root)
    root.mainloop()
