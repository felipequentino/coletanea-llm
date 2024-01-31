import sqlite3

# Função para criar uma tabela no banco de dados
def create_table():
    connection = sqlite3.connect('exemplo.db')
    cursor = connection.cursor()

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS usuarios (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nome TEXT NOT NULL,
            idade INTEGER
        )
    ''')

    connection.commit()
    connection.close()

# Função para inserir um novo usuário no banco de dados
def create_user(nome, idade):
    connection = sqlite3.connect('exemplo.db')
    cursor = connection.cursor()

    cursor.execute('''
        INSERT INTO usuarios (nome, idade) VALUES (?, ?)
    ''', (nome, idade))

    connection.commit()
    connection.close()

# Função para listar todos os usuários
def read_users():
    connection = sqlite3.connect('exemplo.db')
    cursor = connection.cursor()

    cursor.execute('SELECT * FROM usuarios')
    usuarios = cursor.fetchall()

    connection.close()
    return usuarios

# Função para atualizar informações de um usuário
def update_user(user_id, new_nome, new_idade):
    connection = sqlite3.connect('exemplo.db')
    cursor = connection.cursor()

    cursor.execute('''
        UPDATE usuarios
        SET nome=?, idade=?
        WHERE id=?
    ''', (new_nome, new_idade, user_id))

    connection.commit()
    connection.close()

# Função para excluir um usuário
def delete_user(user_id):
    connection = sqlite3.connect('exemplo.db')
    cursor = connection.cursor()

    cursor.execute('DELETE FROM usuarios WHERE id=?', (user_id,))

    connection.commit()
    connection.close()

# Cria a tabela se ela não existir
create_table()

# Exemplos de uso
create_user('João', 25)
create_user('Maria', 30)

print("Usuários antes da atualização:")
print(read_users())

# Atualiza informações de um usuário
update_user(1, 'João Silva', 26)

print("\nUsuários após a atualização:")
print(read_users())

# Exclui um usuário
delete_user(2)

print("\nUsuários após a exclusão:")
print(read_users())