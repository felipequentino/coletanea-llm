import mysql.connector

#Definindo parâmetros de conexão
host = "localhost"
user = "root"
password = ""
database = "mydatabase"

#Criando conexão com o banco de dados
connection = mysql.connector.connect(
    host=host,
    user=user,
    password=password,
    database=database,
)

# Definindo funções para as operações CRUD

def create_record(nome, email):
    """Cria um novo registro no banco de dados."""

    cursor = connection.cursor()
    query = "INSERT INTO clientes (nome, email) VALUES (%s, %s)"
    cursor.execute(query, (nome, email))
    connection.commit()
    cursor.close()

def read_records():
    """Lê todos os registros do banco de dados."""

    cursor = connection.cursor()
    query = "SELECT * FROM clientes"
    cursor.execute(query)
    records = cursor.fetchall()
    cursor.close()
    return records

def update_record(id, nome, email):
    """Atualiza um registro no banco de dados."""

    cursor = connection.cursor()
    query = "UPDATE clientes SET nome=%s, email=%s WHERE id=%s"
    cursor.execute(query, (nome, email, id))
    connection.commit()
    cursor.close()

def delete_record(id):
    """Exclui um registro no banco de dados."""

    cursor = connection.cursor()
    query = "DELETE FROM clientes WHERE id=%s"
    cursor.execute(query, (id,))
    connection.commit()
    cursor.close()

# Exemplos de uso

# Cria um novo registro
create_record("João da Silva", "joao@silva.com")

# Lê todos os registros
records = read_records()
for record in records:
    print(record)

# Atualiza um registro
update_record(1, "Maria da Silva", "maria@silva.com")

# Exclui um registro
delete_record(2)