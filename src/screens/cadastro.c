#include <stdio.h>
#include "../includes/screens.h"
#include "../includes/user.h"
#include "includes/utils.h"

void cadastro(User usuario) {
    clearScreen();
    printf("==================================================\n");
    printf("                   NOVO CADASTRO                  \n");
    printf("==================================================\n");

    printf("Informe um Nome para a conta: ");
    scanf(" %[^\n]s",&usuario.nome);

    printf("Informe um E-mail para a conta: ");
    scanf(" %s",&usuario.email);

    printf("Informe um Senha para a conta: ");
    scanf(" %s",&usuario.senha);

    printf("Informe um Telefone para a conta: ");
    scanf(" %s",&usuario.telefone);

    printf("Informe o endereco da conta (Logradouro): ");
    scanf(" %[^\n]s",&usuario.endereco.logradouro);

    printf("Informe o endereco da conta (Numero): ");
    printf("%d",&usuario.endereco.numero);

    printf("Informe o CEP da conta: ");
    printf(" %s",&usuario.endereco.cep);
}
