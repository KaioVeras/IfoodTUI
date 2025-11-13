#ifndef USER_H
#define USER_H

typedef struct{
    char logradouro[20];
    int numero;
    char cep[10];
} End;

typedef struct{
    char nome[50];
    char email[50];
    char senha[20];
    char telefone[20];
    End endereco;
} User;

#endif