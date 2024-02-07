import psycopg2

#Definindo parâmetros de conexão:

host = "db-rds-aliria.ceck7eanir5p.us-east-1.rds.amazonaws.com"
port = "5432"
database = "bdaliria"
user = "postgres"
password = "aliriards05"

#Criando conexão com o banco de dados:

try:
    connection = psycopg2.connect(
        host=host,
        port=port,
        database=database,
        user=user,
        password=password,
    )
except psycopg2.Error as e:
    print("Erro ao conectar ao banco de dados:", e)
    exit()

cursor = connection.cursor()

#Funções para operações CRUD:

def create_record(nome, email):
    query = """
        INSERT INTO clientes (nome, email)
        VALUES (%s, %s)
        RETURNING id;
    """
    cursor.execute(query, (nome, email))
    connection.commit()
    return cursor.fetchone()[0]


def read_records():
    query = "SELECT * FROM clientes"
    cursor.execute(query)
    return cursor.fetchall()


def update_record(id, nome, email):
    query = """
        UPDATE clientes
        SET nome = %s, email = %s
        WHERE id = %s;
    """
    cursor.execute(query, (nome, email, id))
    connection.commit()


def delete_record(id):
    query = "DELETE FROM clientes WHERE id = %s"
    cursor.execute(query, (id,))
    connection.commit()

#Exemplo de uso:

# Criar novo registro
id_novo_cliente = create_record("João da Silva", "joao@silva.com")

# Ler todos os registros
registros = read_records()
for registro in registros:
    print(f"ID: {registro[0]}")
    print(f"Nome: {registro[1]}")
    print(f"Email: {registro[2]}")
    print()

# Atualizar um registro
update_record(id_novo_cliente, "Maria da Silva", "maria@silva.com")

# Excluir um registro
delete_record(id_novo_cliente)

# Fechar conexão
cursor.close()
connection.close()
