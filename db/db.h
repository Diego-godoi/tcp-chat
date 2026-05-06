#ifndef DATABASE_H
#define DATABASE_H

// Abre (ou cria) o banco de dados
int db_inicializar(const char *caminho_arquivo);

// Salva uma mensagem no banco
// remetente: quem mandou ("eu" ou o nome do outro)
int db_salvar_mensagem(const char *ip_peer, const char *remetente, const char *conteudo);

void db_exibir_historico_por_ip(const char *ip_peer);

// Imprime o histórico de mensagens na tela
void db_exibir_historico();

// Fecha o banco
void db_fechar();

#endif