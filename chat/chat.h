#ifndef CHAT_H
#define CHAT_H

#define TAMANHO_BUFFER 1024
#define TAMANHO_NOME   50

typedef struct {
    int  socket_fd;
    char ip_peer[46];
    char nome_outro[TAMANHO_NOME]; // ← adiciona isso
} DadosRecebimento;

// Inicia o chat P2P (bloqueia até a conversa terminar)
// socket_fd: conexão já estabelecida com o outro peer
// meu_nome:  como você vai aparecer nas mensagens
void chat_iniciar(int socket_fd, const char *meu_nome, const char *ip_peer);

#endif