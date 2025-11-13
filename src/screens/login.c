#include <stdio.h>
#include "../includes/screens.h"
#include "../includes/user.h"
#include  "../includes/utils.h"

void login(User usuario) {
    clearScreen();
    printf("==================================================\n");
    printf("                      LOGIN                       \n");
    printf("==================================================\n");

    printf("Informe o Nome do Conta: ");
    scanf(" %[^\n]s",&usuario.nome);

    printf("Informe o E-mail da Conta: ");
    scanf(" %s",&usuario.email);

    printf("Informe a Senha da Conta: ");
    scanf(" %s",&usuario.senha);
}