#include <stdio.h>
#include <stdlib.h>
#include "../includes/screens.h"

void welcomeScreen() 
{
    int  opcao = 0;

    printf("==================================================\n");
    printf("=                                                =\n");
    printf("=              BEM-VINDO AO IFOOD TUI            =\n");
    printf("=                                                =\n");
    printf("==================================================\n\n");

    printf("> Seus restaurantes favoritos na palma da sua mao!\n");
    printf("> Entrega rapida e segura.\n");
    printf("> Milhares de restaurantes.\n\n");

    printf("[1] Criar minha conta\n");
    printf("[2] Ja tenho uma conta\n\n");

    printf("Selecione uma opcao (1-2): ");
    scanf("%d", &opcao);

    switch(opcao)
    {
    case 1:
        system("cls");
        login();
    break;
    case 2:
        system("cls");
        cadastro();
    break;
    default:
        system("cls");
        printf("Opcao invalida! Tente novamente\n\n");
        welcomeScreen();
        break;
    }
}