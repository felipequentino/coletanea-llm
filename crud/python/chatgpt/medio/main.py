import psycopg2
from psycopg2 import sql

# Função para criar uma tabela no banco de dados
def create_table():
    conn = psycopg2.connect(
        host="db-rds-aliria.ceck7eanir5p.us-east-1.rds.amazonaws.com",
        database="bdaliria",
        user="postgres",
        password="aliriards05"
    )
    cursor = conn.cursor()

    # Criação de tabela de exemplo (usuários)
    create_table_query = '''
        CREATE TABLE IF NOT EXISTS usuarios (
            id SERIAL PRIMARY KEY,
            nome VARCHAR(100) NOT NULL,
            idade INTEGER
        );
    '''
    cursor.execute(create_table_query)
    
    conn.commit()
    cursor.close()
    conn.close()

# Função para inserir um novo usuário no banco de dados
def create_user(nome, idade):
    conn = psycopg2.connect(
        host="db-rds-aliria.ceck7eanir5p.us-east-1.rds.amazonaws.com",
        database="bdaliria",
        user="postgres",
        password="aliriards05"
    )
    cursor = conn.cursor()

    insert_query = sql.SQL('INSERT INTO usuarios (nome, idade) VALUES ({}, {})').format(
        sql.Literal(nome),
        sql.Literal(idade)
    )
    cursor.execute(insert_query)

    conn.commit()
    cursor.close()
    conn.close()

# Função para listar todos os usuários
def read_users():
    conn = psycopg2.connect(
        host="db-rds-aliria.ceck7eanir5p.us-east-1.rds.amazonaws.com",
        database="bdaliria",
        user="postgres",
        password="aliriards05"
    )
    cursor = conn.cursor()

    select_query = 'SELECT * FROM usuarios;'
    cursor.execute(select_query)
    usuarios = cursor.fetchall()

    cursor.close()
    conn.close()
    return usuarios

# Função para atualizar informações de um usuário
def update_user(user_id, new_nome, new_idade):
    conn = psycopg2.connect(
        host="db-rds-aliria.ceck7eanir5p.us-east-1.rds.amazonaws.com",
        database="bdaliria",
        user="postgres",
        password="aliriards05"
    )
    cursor = conn.cursor()

    update_query = sql.SQL('''
        UPDATE usuarios
        SET nome = {}, idade = {}
        WHERE id = {};
    ''').format(
        sql.Literal(new_nome),
        sql.Literal(new_idade),
        sql.Literal(user_id)
    )
    cursor.execute(update_query)

    conn.commit()
    cursor.close()
    conn.close()

# Função para excluir um usuário
def delete_user(user_id):
    conn = psycopg2.connect(
        host="db-rds-aliria.ceck7eanir5p.us-east-1.rds.amazonaws.com",
        database="bdaliria",
        user="postgres",
        password="aliriards05"
    )
    cursor = conn.cursor()

    delete_query = sql.SQL('DELETE FROM usuarios WHERE id = {}').format(
        sql.Literal(user_id)
    )
    cursor.execute(delete_query)

    conn.commit()
    cursor.close()
    conn.close()

if __name__ == '__main__':
    # Crie a tabela se ela não existir
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