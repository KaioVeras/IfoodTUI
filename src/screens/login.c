#include <stdio.h>
#include <stdlib.h>
#include "../includes/screens.h"
#include "../includes/user.h"

void login(User usuario) {


    system("cls");
    printf("==================================================\n");
    printf("                      LOGIN                       \n");
    printf("==================================================\n");

    printf("Informe o nome do login: ");
    scanf(" %s",&usuario.nome);
}