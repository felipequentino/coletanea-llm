import tkinter as tk
from tkinter import messagebox

class TodoApp:
    def __init__(self, root):
        self.root = root
        self.root.title("To-Do List")

        # Lista para armazenar as tarefas
        self.tasks = []

        # Componentes GUI
        self.task_entry = tk.Entry(root, width=30)
        self.task_entry.grid(row=0, column=0, padx=10, pady=10)

        self.add_button = tk.Button(root, text="Adicionar Tarefa", command=self.add_task)
        self.add_button.grid(row=0, column=1, padx=10, pady=10)

        self.task_listbox = tk.Listbox(root, selectmode=tk.SINGLE, width=40, height=10)
        self.task_listbox.grid(row=1, column=0, columnspan=2, padx=10, pady=10)

        self.remove_button = tk.Button(root, text="Remover Tarefa", command=self.remove_task)
        self.remove_button.grid(row=2, column=0, padx=10, pady=10)

        self.complete_button = tk.Button(root, text="Marcar como Concluída", command=self.mark_as_complete)
        self.complete_button.grid(row=2, column=1, padx=10, pady=10)

        self.save_button = tk.Button(root, text="Salvar Tarefas", command=self.save_tasks)
        self.save_button.grid(row=3, column=0, columnspan=2, padx=10, pady=10)

        # Carregar tarefas salvas
        self.load_tasks()

    def add_task(self):
        task = self.task_entry.get()
        if task:
            self.tasks.append(task)
            self.update_task_listbox()

            # Limpar a entrada após adicionar a tarefa
            self.task_entry.delete(0, tk.END)
        else:
            messagebox.showwarning("Aviso", "Por favor, insira uma tarefa.")

    def remove_task(self):
        selected_index = self.task_listbox.curselection()
        if selected_index:
            self.tasks.pop(selected_index[0])
            self.update_task_listbox()

    def mark_as_complete(self):
        selected_index = self.task_listbox.curselection()
        if selected_index:
            # Adicione um indicador (por exemplo, '[Concluída]') à tarefa concluída
            self.tasks[selected_index[0]] = f"[Concluída] {self.tasks[selected_index[0]]}"
            self.update_task_listbox()

    def update_task_listbox(self):
        self.task_listbox.delete(0, tk.END)
        for task in self.tasks:
            self.task_listbox.insert(tk.END, task)

    def save_tasks(self):
        with open("tasks.txt", "w") as file:
            for task in self.tasks:
                file.write(task + "\n")

    def load_tasks(self):
        try:
            with open("tasks.txt", "r") as file:
                self.tasks = [line.strip() for line in file.readlines()]
                self.update_task_listbox()
        except FileNotFoundError:
            pass

if __name__ == "__main__":
    root = tk.Tk()
    app = TodoApp(root)
    root.mainloop()
