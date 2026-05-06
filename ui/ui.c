#include "ui.h"
#include <stdio.h>
#include <string.h>

OpcaoMenu ui_menu_principal(){
    int opcao;
    printf("\n╔══════════════════════╗\n");
    printf("║    TCP Chat P2P      ║\n");
    printf("╠══════════════════════╣\n");
    printf("║ 1. Hospedar chat     ║\n");
    printf("║ 2. Conectar a alguém ║\n");
    printf("║ 3. Ver histórico     ║\n");
    printf("║ 4. Sair              ║\n");
    printf("╚══════════════════════╝\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar(); // limpa o stdin
    return (OpcaoMenu)opcao;
}

void ui_pedir_texto(const char *pergunta, char *buffer, int tamnho){
    printf("%s: ", pergunta);
    fgets(buffer, tamnho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; //remove o \n
}

int ui_pedir_numero(const char *pergunta){
    int numero;
    printf("%s: ", pergunta);
    scanf("%d", &numero);
    getchar();
    return numero;
}

void ui_exibir_mensagem_chat(const char *remetente, const char *conteudo){
    printf("    %s -> %s\n", remetente, conteudo);
}

void ui_exibir_mensagem(const char *msg){
    printf("    %s\n", msg);
}