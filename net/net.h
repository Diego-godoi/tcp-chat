#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>

// Cria um socket servidor já pronto para aceitar conexoes
int network_criar_servidor(int porta);

// Conecta um socket cliente e conecta ao servidor
int network_conectar_servidor(const char *ip, int porta);

// Aceita uma nova conexao (retorna o fd do novo cliente)
int network_aceitar_conexao(int socket_servidor, char *ip_buffer, int ip_tamanho);

// Envia uma mensagem por um socket
int network_enviar(int socket_fd, const char *mensagem);

// Recebe uma mensagem de um socket no buffer
int network_receber(int socket_fd, char *buffer, int tamanho);

//Fecha um socket
void network_fechar(int socket_fd);

#endif
