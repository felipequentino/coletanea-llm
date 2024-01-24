import tkinter as tk
from tkinter import messagebox

def adicionar_tarefa():
    tarefa = entry.get()
    if tarefa:
        lista_tarefas.insert(tk.END, tarefa)
        entry.delete(0, tk.END)
    else:
        messagebox.showwarning("Aviso", "Por favor, insira uma tarefa.")

def remover_tarefa():
    try:
        selecionado = lista_tarefas.curselection()
        lista_tarefas.delete(selecionado)
    except:
        messagebox.showwarning("Aviso", "Por favor, selecione uma tarefa para remover.")

# Criar a janela principal
janela = tk.Tk()
janela.title("To-Do List")

# Entrada para adicionar tarefas
entry = tk.Entry(janela, width=40)
entry.pack(pady=10)

# Botões para adicionar e remover tarefas
btn_adicionar = tk.Button(janela, text="Adicionar Tarefa", command=adicionar_tarefa)
btn_adicionar.pack(pady=5)
btn_remover = tk.Button(janela, text="Remover Tarefa", command=remover_tarefa)
btn_remover.pack(pady=5)

# Lista de tarefas
lista_tarefas = tk.Listbox(janela, selectmode=tk.SINGLE, width=40, height=10)
lista_tarefas.pack(pady=10)

# Iniciar a janela principal
janela.mainloop()
