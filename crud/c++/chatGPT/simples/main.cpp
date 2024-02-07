#include <iostream>
#include <sqlite3.h>

// Função para criar uma tabela no banco de dados
void create_table(sqlite3 *db) {
    char *errMsg = nullptr;
    const char *sql = "CREATE TABLE IF NOT EXISTS usuarios ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "nome TEXT NOT NULL,"
                      "idade INTEGER"
                      ");";

    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao criar tabela: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Função para inserir um novo usuário no banco de dados
void create_user(sqlite3 *db, const std::string &nome, int idade) {
    char *errMsg = nullptr;
    std::string sql = "INSERT INTO usuarios (nome, idade) VALUES ('" + nome + "', " + std::to_string(idade) + ");";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao inserir usuário: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

// Função para listar todos os usuários
void read_users(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM usuarios;";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar a consulta: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "Usuários:" << std::endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        int idade = sqlite3_column_int(stmt, 2);
        std::cout << "ID: " << id << ", Nome: " << nome << ", Idade: " << idade << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao ler os usuários: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("exemplo.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Cria a tabela se ela não existir
    create_table(db);

    // Exemplos de uso
    create_user(db, "João", 25);
    create_user(db, "Maria", 30);

    read_users(db);

    sqlite3_close(db);
    return 0;
}
