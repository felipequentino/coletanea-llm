#include <iostream>
#include <pqxx/pqxx>

// Função para criar uma tabela no banco de dados
void create_table(pqxx::connection &conn) {
    pqxx::work txn(conn);
    txn.exec(R"(
        CREATE TABLE IF NOT EXISTS usuarios (
            id SERIAL PRIMARY KEY,
            nome TEXT NOT NULL,
            idade INTEGER
        )
    )");
    txn.commit();
}

// Função para inserir um novo usuário no banco de dados
void create_user(pqxx::connection &conn, const std::string &nome, int idade) {
    pqxx::work txn(conn);
    txn.exec_params("INSERT INTO usuarios (nome, idade) VALUES ($1, $2)", nome, idade);
    txn.commit();
}

// Função para listar todos os usuários
void read_users(pqxx::connection &conn) {
    pqxx::work txn(conn);
    pqxx::result result = txn.exec("SELECT * FROM usuarios");
    txn.commit();

    std::cout << "Usuários:" << std::endl;
    for (const auto &row : result) {
        std::cout << "ID: " << row[0].as<int>() << ", Nome: " << row[1].as<std::string>() << ", Idade: " << row[2].as<int>() << std::endl;
    }
}

int main() {
    try {
        // Conecta ao banco de dados
        pqxx::connection conn("dbname=seu_banco_de_dados user=seu_usuario password=sua_senha");

        // Cria a tabela se ela não existir
        create_table(conn);

        // Exemplos de uso
        create_user(conn, "João", 25);
        create_user(conn, "Maria", 30);

        read_users(conn);
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
