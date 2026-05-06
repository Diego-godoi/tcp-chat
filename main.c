#include <stdio.h>
#include "net/net.h"
#include "chat/chat.h"
#include "db/db.h"
#include "ui/ui.h"


int main(){
    char meu_nome[50];
    char ip[50];
    int porta;
    int socket_fd = -1;

    if(db_inicializar("chat.db")<0) return 1;

    ui_pedir_texto("Seu nome", meu_nome, sizeof(meu_nome));

    OpcaoMenu opcao = ui_menu_principal();

    switch(opcao){
        case OPCAO_HOSPEDAR:
            porta = ui_pedir_numero("Posta para hospedar (ex:8080)");
            printf("Aguardando conexao na porta %d...\n", porta);

            char ip_do_peer[46];
            int servidor = network_criar_servidor(porta);
            socket_fd = network_aceitar_conexao(servidor, ip_do_peer, sizeof(ip_do_peer));
            network_fechar(servidor); //nao precisa mais do servidor apos conectar

            
            printf("[Alguem conectou! Iniciando chat...]\n");
            db_exibir_historico_por_ip(ip_do_peer);
            chat_iniciar(socket_fd, meu_nome, ip_do_peer);
            break;

        case OPCAO_CONECTAR:
            ui_pedir_texto("IP do host (ex: 192.169.1.10)", ip, sizeof(ip));
            porta = ui_pedir_numero("Porta (ex: 8080)");

            socket_fd = network_conectar_servidor(ip, porta);
            if(socket_fd < 0){
                printf("Nao foi possivel conectar.\n");
                break;
            }

            printf("[Conectado! Iniciando chat...]\n");
            db_exibir_historico_por_ip(ip);
            chat_iniciar(socket_fd, meu_nome, ip_do_peer);
            break;
        
        case OPCAO_HISTORICO:
            db_exibir_historico();
            break;

        case OPCAO_SAIR:
            printf("Ate logo!\n");
            break;
    }

    if(socket_fd >= 0) network_fechar(socket_fd);
    db_fechar();
    return 0;
}