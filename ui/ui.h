#ifndef UI_H
#define UI_H

typedef enum {
    OPCAO_HOSPEDAR  = 1,
    OPCAO_CONECTAR  = 2,
    OPCAO_HISTORICO = 3,
    OPCAO_SAIR      = 4
} OpcaoMenu;

// Mostra o menu e retorna a opção escolhida
OpcaoMenu ui_menu_principal();

// Pede uma string ao usuário (nome, IP, etc)
void ui_pedir_texto(const char *pergunta, char *buffer, int tamanho);

// Pede um número (porta)
int ui_pedir_numero(const char *pergunta);

// Exibe mensagem de chat formatada
void ui_exibir_mensagem_chat(const char *remetente, const char *conteudo);

void ui_exibir_mensagem(const char *msg);

#endif