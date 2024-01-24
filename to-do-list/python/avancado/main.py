import tkinter as tk
from tkinter import ttk
import sqlite3
from datetime import datetime
from tkcalendar import Calendar

class TodoApp:
    def __init__(self, root):
        self.root = root
        self.root.title("To-Do List")
        self.root.geometry("600x400")

        # Conectar ao banco de dados SQLite
        self.conn = sqlite3.connect("todo.db")
        self.cursor = self.conn.cursor()

        # Criar tabela se não existir
        self.cursor.execute('''
            CREATE TABLE IF NOT EXISTS tasks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT,
                description TEXT,
                due_date DATE,
                priority TEXT,
                category TEXT,
                completed INTEGER,
                notes TEXT
            )
        ''')
        self.conn.commit()

        # Criar e configurar widgets
        self.create_widgets()

    def create_widgets(self):
        # Título
        title_label = ttk.Label(self.root, text="To-Do List", font=("Helvetica", 16))
        title_label.grid(row=0, column=0, columnspan=2, pady=10)

        # Formulário de Adição de Tarefas
        self.title_var = tk.StringVar()
        self.description_var = tk.StringVar()
        self.due_date_var = tk.StringVar()
        self.priority_var = tk.StringVar()
        self.category_var = tk.StringVar()

        ttk.Label(self.root, text="Título:").grid(row=1, column=0, sticky="e")
        ttk.Entry(self.root, textvariable=self.title_var).grid(row=1, column=1)
        ttk.Label(self.root, text="Descrição:").grid(row=2, column=0, sticky="e")
        ttk.Entry(self.root, textvariable=self.description_var).grid(row=2, column=1)
        ttk.Label(self.root, text="Data de Vencimento:").grid(row=3, column=0, sticky="e")
        ttk.Entry(self.root, textvariable=self.due_date_var).grid(row=3, column=1)
        ttk.Label(self.root, text="Prioridade:").grid(row=4, column=0, sticky="e")
        priority_combobox = ttk.Combobox(self.root, values=["Alta", "Média", "Baixa"], textvariable=self.priority_var)
        priority_combobox.grid(row=4, column=1)
        ttk.Label(self.root, text="Categoria:").grid(row=5, column=0, sticky="e")
        category_combobox = ttk.Combobox(self.root, values=["Trabalho", "Pessoal", "Estudos"], textvariable=self.category_var)
        category_combobox.grid(row=5, column=1)

        ttk.Button(self.root, text="Selecionar Data", command=self.choose_due_date).grid(row=3, column=2)

        # Botão para adicionar tarefa
        ttk.Button(self.root, text="Adicionar Tarefa", command=self.add_task).grid(row=6, column=0, columnspan=2, pady=10)

        # Lista de Tarefas Pendentes
        self.tree = ttk.Treeview(self.root, columns=("Title", "Description", "Due Date", "Priority", "Category"))
        self.tree.heading("#0", text="ID")
        self.tree.heading("Title", text="Título")
        self.tree.heading("Description", text="Descrição")
        self.tree.heading("Due Date", text="Data de Vencimento")
        self.tree.heading("Priority", text="Prioridade")
        self.tree.heading("Category", text="Categoria")
        self.tree.grid(row=7, column=0, columnspan=3, pady=10)

        # Carregar tarefas existentes
        self.load_tasks()

        # Botão para remover tarefa
        ttk.Button(self.root, text="Remover Tarefa", command=self.remove_task).grid(row=8, column=0, columnspan=3, pady=10)

        # Botão para marcar como concluída
        ttk.Button(self.root, text="Concluir Tarefa", command=self.complete_task).grid(row=9, column=0, columnspan=3, pady=10)

    def choose_due_date(self):
        top = tk.Toplevel(self.root)
        cal = Calendar(top, selectmode="day", year=datetime.now().year, month=datetime.now().month, day=datetime.now().day)
        cal.grid(row=0, column=0, columnspan=3)

        def set_due_date():
            self.set_due_date(cal.get_date())
            top.destroy()

        ttk.Button(top, text="Selecionar Data", command=set_due_date).grid(row=1, column=0, columnspan=3, pady=10)

    def set_due_date(self, date):
        self.due_date_var.set(date)

    def add_task(self):
        title = self.title_var.get()
        description = self.description_var.get()
        due_date = self.due_date_var.get()
        priority = self.priority_var.get()
        category = self.category_var.get()

        if title and due_date:
            self.cursor.execute('''
                INSERT INTO tasks (title, description, due_date, priority, category, completed)
                VALUES (?, ?, ?, ?, ?, 0)
            ''', (title, description, due_date, priority, category))
            self.conn.commit()
            self.clear_fields()
            self.load_tasks()

    def remove_task(self):
        selected_item = self.tree.selection()
        if selected_item:
            task_id = self.tree.item(selected_item, "values")[0]
            self.cursor.execute("DELETE FROM tasks WHERE id=?", (task_id,))
            self.conn.commit()
            self.load_tasks()

    def complete_task(self):
        selected_item = self.tree.selection()
        if selected_item:
            task_id = self.tree.item(selected_item, "values")[0]
            self.cursor.execute("UPDATE tasks SET completed=1 WHERE id=?", (task_id,))
            self.conn.commit()
            self.load_tasks()

    def load_tasks(self):
        self.tree.delete(*self.tree.get_children())
        tasks = self.cursor.execute('''
            SELECT id, title, description, due_date, priority, category
            FROM tasks
            WHERE completed=0
            ORDER BY due_date, priority
        ''').fetchall()
        for task in tasks:
            self.tree.insert("", "end", values=task)

    def clear_fields(self):
        self.title_var.set("")
        self.description_var.set("")
        self.due_date_var.set("")
        self.priority_var.set("")
        self.category_var.set("")

if __name__ == "__main__":
    root = tk.Tk()
    app = TodoApp(root)
    root.mainloop()
