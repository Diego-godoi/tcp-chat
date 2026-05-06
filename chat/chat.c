#include "chat.h"
#include "../net/net.h"
#include "../db/db.h"
#include "../ui/ui.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

static void *thread_receber(void *arg){
    DadosRecebimento *dados = (DadosRecebimento *)arg; //dados recebe os argumentos do parametro
    char buffer[TAMANHO_BUFFER];

    while(1){
        int bytes = network_receber(dados->socket_fd, buffer, TAMANHO_BUFFER);

        if(bytes <=0){
            ui_exibir_mensagem("\n[O outro usuario desconectou]");
            exit(0);
        }
         //formato da mensagem "NOME:mensagem"
        char *separador = strchr(buffer, ':'); // separa a string em duas. primeiro lado vai para o buffer e outro para separador
        if (separador  != NULL){
            *separador = '\0';
            char *nome = buffer;
            char *conteudo = separador +1;

            ui_exibir_mensagem_chat(nome, conteudo);
            db_salvar_mensagem(dados->ip_peer, nome, conteudo);
        }
    }
    return NULL;
}

void chat_iniciar(int socket_fd, const char *meu_nome, const char *ip_peer){
    char buffer[TAMANHO_BUFFER];
    char mensagem_formatada[TAMANHO_BUFFER + TAMANHO_NOME];

    DadosRecebimento dados;
    dados.socket_fd = socket_fd;
    strncpy(dados.nome_outro,meu_nome, TAMANHO_NOME - 1);
    strncpy(dados.ip_peer,ip_peer, sizeof(dados.ip_peer));

    pthread_t thread;
    pthread_create(&thread, NULL, thread_receber, &dados);
    pthread_detach(thread); // nao sei oq faz

    printf("\n[Chat iniciado! Digite /sair para encerrar]\n\n");

    while(1){
        fgets(buffer, TAMANHO_BUFFER, stdin); // Le o input

        buffer[strcspn(buffer, "\n")] = '\0'; //remove o \n odo fgets e coloca o \0

        if (strcspn(buffer, "/sair") == 0){
            printf("[Voce saiu do chat]\n");
            break;
        }

        if(strlen(buffer) == 0) continue; //se nao digitou nada - continue

        snprintf(mensagem_formatada, sizeof(mensagem_formatada), "%s:%s", meu_nome, buffer); // formata a mensagem nome:mensagem

        network_enviar(socket_fd, mensagem_formatada);

        db_salvar_mensagem(ip_peer, meu_nome, buffer);
    }
}