#include "db.h"
#include <sqlite3.h>
#include <stdio.h>

static sqlite3 *banco = NULL;

int db_inicializar(const char *caminho_arquivo){
    if(sqlite3_open(caminho_arquivo, &banco) != SQLITE_OK){
        printf("Erro ao abrir banco: %s\n", sqlite3_errmsg(banco));
        return -1;
    }

    const char *sql_criar_tabela = 
    "CREATE TABLE IF NOT EXISTS mensagens ("
    " id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "ip_peer TEXT NOT NULL,"
    "remetente TEXT NOT NULL,"
    "conteudo TEXT NOT NULL,"
    "horario DATIME DEFAULT CURRENT_TIMESTAMP"
    ");";

    char *erro = NULL;

    if (sqlite3_exec(banco, sql_criar_tabela, NULL, NULL, &erro) != SQLITE_OK){
        printf("Erro ao criar tabela: %s\n", erro);
        sqlite3_free(erro); //limpa o erro (ponteiro aponta para null agora)
        return -1;
    }
    return 0;
}

int db_salvar_mensagem(const char *ip_peer, const char *remetente, const char *conteudo){
    // usa prepare statement - sql injection
    const char *sql = "INSERT INTO mensagens (ip_peer, remetente, conteudo) VALUES (?,?);";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(banco, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, ip_peer, -1, SQLITE_STATIC); // substitui o segundo valor
    sqlite3_bind_text(stmt, 2, remetente, -1, SQLITE_STATIC); // substitui o primeiro valor
    sqlite3_bind_text(stmt, 2, conteudo, -1, SQLITE_STATIC); // substitui o segundo valor

    sqlite3_step(stmt); //executa
    sqlite3_finalize(stmt); //libera memoria da query
    return 0;
}

// Callback chamado pra cada linha encontrada no SELECT
static int callback_historico(void *nao_usado, int colunas,
                               char **valores, char **nomes_colunas) {
    // valores[0]=id, valores[1]=remetente, valores[2]=conteudo, valores[3]=horario
    printf("[%s] %s: %s\n", valores[3], valores[1], valores[2]);
    return 0;
}

void db_exibir_historico_por_ip(const char *ip_peer) {
    const char *sql =
        "SELECT remetente, conteudo, horario "
        "FROM mensagens "
        "WHERE ip_peer = ? "
        "ORDER BY id;";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(banco, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, ip_peer, -1, SQLITE_STATIC);

    printf("\n── Histórico com %s ──\n", ip_peer);

    int encontrou = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        encontrou = 1;
        const char *remetente = (const char *)sqlite3_column_text(stmt, 0);
        const char *conteudo  = (const char *)sqlite3_column_text(stmt, 1);
        const char *horario   = (const char *)sqlite3_column_text(stmt, 2);
        printf("  [%s] %s: %s\n", horario, remetente, conteudo);
    }

    if (!encontrou) printf("  (nenhuma conversa anterior)\n");

    printf("──────────────────────────\n\n");
    sqlite3_finalize(stmt);
}

void db_exibir_historico() {
    printf("\n--- Histórico de mensagens ---\n");
    const char *sql = "SELECT id, remetente, conteudo, horario FROM mensagens ORDER BY id;";
    char *erro = NULL;
    sqlite3_exec(banco, sql, callback_historico, NULL, &erro);
    printf("------------------------------\n\n");
}

void db_fechar(){
    if(banco != NULL){
        sqlite3_close(banco);
        banco = NULL;
    }
}