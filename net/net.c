#include "net.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int network_criar_servidor(int porta){
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0){
        printf("Erro ao criar socket");
        return -1;
    }
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // permite o reuso do socket

    struct sockaddr_in endereco;
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(porta); // converte para binario
    endereco.sin_addr.s_addr = INADDR_ANY; // aceita qualquer IP

    if (bind(fd, (struct sockaddr *)&endereco, sizeof(endereco))<0){
        printf("Erro no bind");
        return -1;
    }

    if(listen(fd,10)< 0){ //escuta ate 10 conexoes?
        printf("Erro no listen");
        return -1;
    }
    return fd; // retorna o proprio file descriptor
}

int network_conectar_servidor(const char *ip, int porta){
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0){
        printf("Erro ao criar socket");
        return -1;
    }
    struct sockaddr_in endereco;
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(porta);

    inet_pton(AF_INET, ip, &endereco.sin_addr); // converte IP(server) string para binario

    if(connect(fd, (struct sockaddr *)&endereco, sizeof(endereco))<0){
        printf("Erro ao conectar");
        return -1;
    }
    return fd; // retorna o proprio file descriptor
}

int network_aceitar_conexao(int socket_servidor, char *ip_buffer, int ip_tamanho){
    struct sockaddr_in endereco_cliente;
    socklen_t tamanho = sizeof(endereco_cliente);

    int fd_cliente = accept(socket_servidor, (struct sockaddr *)&endereco_cliente, &tamanho);

    if(fd_cliente < 0){
        printf("Erro no accept com o cliente");
        return -1;
    }

    // converte binario para string
    inet_ntop(AF_INET, &endereco_cliente.sin_addr, ip_buffer, ip_tamanho);
    return fd_cliente; // retorna o file descriptor da conexao
}

int network_enviar(int socket_fd, const char *mensagem){
    return send(socket_fd, mensagem, strlen(mensagem), 0); //envia uma mensagem para o fd do socket (srever ou clietne)
}

int network_receber(int socket_fd, char *buffer, int tamanho){
    memset(buffer, 0, tamanho); //limpa o buffer
    return recv(socket_fd, buffer, tamanho -1, 0); // metodo que recebe uma mensagem do tamnho -1 que vai no buffer (passamos nosso fd para receber a mensagem)
}

void network_fechar(int socket_fd){
    close(socket_fd); //fecha a conexao do fd
}