import sqlite3

def create_table():
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)''')
    conn.commit()
    conn.close()

def create(name, age):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (name, age) VALUES (?, ?)", (name, age))
    conn.commit()
    conn.close()

def read(id):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE id=?", (id,))
    user = c.fetchone()
    conn.close()
    return user

def update(id, name, age):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("UPDATE users SET name=?, age=? WHERE id=?", (name, age, id))
    conn.commit()
    conn.close()

def delete(id):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("DELETE FROM users WHERE id=?", (id,))
    conn.commit()
    conn.close()

def main():
    create_table()

    # Criação de um usuário
    create("John Doe", 30)

    # Leitura de um usuário
    user_id = 1
    user = read(user_id)
    print(f"User {user_id}: {user}")

    # Atualização de um usuário
    update(user_id, "Jane Doe", 28)
    user = read(user_id)
    print(f"User {user_id} after update: {user}")

    # Remoção de um usuário
    delete(user_id)
    user = read(user_id)
    print(f"User {user_id} after deletion: {user}")

if __name__ == "__main__":
    main()