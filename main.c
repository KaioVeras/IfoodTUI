#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>

// Inclusão de bibliotecas específicas para Windows
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
#endif

// Definição das Structs
struct Endereco
{
    char endereco[20];
    char logradouro[10];
    char cep[11];
    int numero;
};

struct Cliente
{
    struct Endereco end;
    char nome[30];
    char cpf[11];
    char email[20];
    char telefone[20];
    char senha[20];
};

// Protótipos dos Procedimentso
void menu_ui();
void login_ui();
void cadastro_ui();
void clearScreen();
void limparBuffer();
void code_ui(struct Cliente *cliente);
void login_error_ui();
void endereco_ui();
void modo_cliente_ui(struct Cliente *cliente);
void modo_entregador_ui();
void modo_restaurante_ui();
void configurarAcentuacao();

/// Protótipos das Funções
int menu(int opcao);
int menu_tipo();
int cadastro(struct Cliente *cliente);
int logar(struct Cliente *cliente);
int le_valida_verificacao(struct Cliente *cliente);
int endereco(struct Endereco *end);

int main()
{
    configurarAcentuacao();
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    struct Cliente cliente;
    int opcao = 0, tipo = 0;

    // Inicializa a struct com valores vazios
    memset(&cliente, 0, sizeof(struct Cliente));

    // Loop do menu
    do
    {
        menu_ui();
        opcao = menu(opcao);

        switch (opcao)
        {
        case 1:
            if (strlen(cliente.nome) != 0)
            {
                clearScreen();
                printf("Usuario ja cadastrado! Tente logar.\n");
                printf("\nPressione ENTER para continuar...");
                limparBuffer();
                getchar();
            }
            else
            {
                cadastro(&cliente);
                endereco(&cliente.end);
                le_valida_verificacao(&cliente);
            }
            break;

        case 2:
            if (strlen(cliente.nome) == 0)
            {
                clearScreen();
                printf("Nenhum usuario cadastrado! Cadastre-se primeiro.\n");
                printf("\nPressione ENTER para continuar...");
                limparBuffer();
                getchar();
            }
            else
            {
                logar(&cliente);

                tipo = menu_tipo(&cliente);

                switch (tipo)
                {
                case 1:
                    clearScreen();
                    printf("Bem-vindo, Cliente %s!\n", cliente.nome);
                    printf("Endereço cadastrado: %s, %s, %d, CEP: %s\n", cliente.end.endereco, cliente.end.logradouro, cliente.end.numero, cliente.end.cep);
                    printf("\nPressione ENTER para continuar...");
                    limparBuffer();
                    getchar();
                    break;

                case 2:
                    clearScreen();
                    printf("Bem-vindo, Entregador %s!\n", cliente.nome);
                    printf("\nPressione ENTER para continuar...");
                    limparBuffer();
                    getchar();
                    break;

                case 3:
                    clearScreen();
                    printf("Bem-vindo, Restaurante %s!\n", cliente.nome);
                    printf("\nPressione ENTER para continuar...");
                    limparBuffer();
                    getchar();
                    break;

                case 4:

                    break;
                }
            }
            break;

        case 3:
            clearScreen();
            printf("Programa Finalizado\n");
            break;

        default:
            clearScreen();
            printf("Opcao invalida, tente novamente\n");
        }
    } while (opcao != 3);

    return 0;
}

// Função do menu inicial
int menu(int opcao)
{
    int cont = 0;

    printf("[1] >> Cadastrar\n");
    printf("[2] >> Logar\n");
    printf("[3] >> Sair\n\n");

    do
    {
        if (cont > 0)
        {
            printf("Opcao invalida! Tente novamente: ");
        }
        printf("Entre o numero desejado: ");
        if (scanf("%d", &opcao) != 1)
        {
            limparBuffer();
            opcao = 0;
        }
        cont++;
    } while (opcao != 3 && opcao != 1 && opcao != 2);

    return opcao;
}

// Função do menu do tipo de usuário
int menu_tipo(struct Cliente *cliente)
{
    int cont = 0;
    int tipo = 0;

    modo_cliente_ui(&cliente);

    printf("[1] >> Cliente\n");
    printf("[2] >> Entregador\n");
    printf("[3] >> Restaurante\n\n");
    printf("[4] >> Voltar\n");

    do
    {
        if (cont > 0)
        {
            printf("Opcao invalida! Tente novamente: ");
        }
        printf("Entre o numero desejado: ");
        if (scanf("%d", &tipo) != 1)
        {
            limparBuffer();
            tipo = 0;
        }
        cont++;
    } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4);

    return tipo;
}

// Função de cadastro
int cadastro(struct Cliente *cliente)
{
    char nome[50];
    char email[50];
    char senha[20];
    int i = 0, ultimo_espaco = 0;

    cadastro_ui();

    printf("Digite seu nome: ");
    scanf(" %[^\n]s", nome);

    for (i = 0; i < strlen(nome); i++)
    {
        if (nome[i] == ' ')
        {
            ultimo_espaco = i + 1;
        }
    }

    nome[0] = toupper(nome[0]);
    if (ultimo_espaco > 0)
    {
        nome[ultimo_espaco] = toupper(nome[ultimo_espaco]);
    }

    printf("Digite seu email: ");
    scanf(" %s", email);

    printf("Digite sua senha: ");
    scanf(" %s", senha);

    strcpy(cliente->nome, nome);
    strcpy(cliente->email, email);
    strcpy(cliente->senha, senha);

    printf("\nCadastro realizado com sucesso!!\n");
    printf(">> Pressione ENTER para continuar...");
    limparBuffer();
    getchar();
    return 0;
}

// Função de login
int logar(struct Cliente *cliente)
{
    char email[50];
    char senha[20];

    login_ui();

    do
    {
        printf("Digite seu email: ");
        scanf(" %s", email);

        printf("Digite sua senha: ");
        scanf(" %s", senha);

        if (strcmp(email, cliente->email) != 0 || strcmp(senha, cliente->senha) != 0)
        {
            login_error_ui();
            printf("Email ou senha incorretos! Tente novamente.\n");
        }
    } while (strcmp(email, cliente->email) != 0 || strcmp(senha, cliente->senha) != 0);

    printf("\nLogin realizado com sucesso!!\n");
    printf(">> Pressione ENTER para continuar...");
    limparBuffer();
    getchar();
    return 0;
}

// Função de endereço
int endereco(struct Endereco *end)
{
    endereco_ui();

    printf("Digite o endereco: ");
    scanf(" %19[^\n]", end->endereco);

    printf("Digite o logradouro: ");
    scanf(" %9[^\n]", end->logradouro);

    printf("Digite o CEP: ");
    scanf(" %10s", end->cep);

    printf("Digite o numero: ");
    if (scanf(" %d", &end->numero) != 1)
    {
        limparBuffer();
        end->numero = 0;
    }

    printf("\nEndereco cadastrado com sucesso!!\n");
    printf(">> Pressione ENTER para continuar...");
    limparBuffer();
    getchar();
    return 0;
}

// Função de teste de código
int testecodigo(struct Cliente *cliente)
{

    if (le_valida_verificacao(cliente))
    {
        printf("\nAcesso Concedido. Bem-vindo ao sistema\n");
    }
    else
    {
        printf("Acesso Negado, tente novamente.\n");
    }

    return 0;
}

// Função para gerar código aleatório
int gerar_codigo()
{
    int codigo;

    // Gera um número aleatório de 5 dígitos (100000 a 999999)
    codigo = 100000 + (rand() % 900000);

    return codigo;
}

// Função para ler e validar o código
int le_valida_verificacao(struct Cliente *cliente)
{
    int codigo_correto = 0;
    codigo_correto = gerar_codigo();
    int codigo_inserido = 0;
    
    code_ui(cliente);
    printf("Insira o código (%d): ", codigo_correto);
    
    if (scanf("%d", &codigo_inserido) != 1){
        limparBuffer();
        codigo_inserido = 0;
    }

    do{
        if (codigo_inserido == codigo_correto){
            printf("\nCódigo validado com sucesso.\n");
            printf(">> Pressione ENTER para continuar...");
            limparBuffer();
            getchar();
            break;
        } else{
            printf("Código Inválido! Tente novamente (%d): ", codigo_correto);
            if (scanf("%d", &codigo_inserido) != 1)
            {
                limparBuffer();
                codigo_inserido = 0;
            }
        }
    } while (!(codigo_inserido == codigo_correto));

    return 0;
}

// Procedimento para limpar a tela de acordo com o sistema operacional
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Procedimento para limpar o buffer do teclado
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Procedimento para configurar a acentuação
void configurarAcentuacao()
{
#ifdef _WIN32
    // Habilita suporte a UTF-8 no console do Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Configura locale para UTF-8
    setlocale(LC_ALL, ".UTF8");
#else
    // Para Linux/Mac, configura locale para UTF-8
    setlocale(LC_ALL, "");
#endif
}

// Procedimentos de Interface do Usuário (UI)
void menu_ui()
{
    clearScreen();
    printf("===============================================================================\n");
    printf("||                                                                           ||\n");
    printf("||      IIIII  FFFFFF  OOO   OOO   DDD           TTTTTTT  U   U  IIIII       ||\n");
    printf("||        I    F      O   O O   O  D  D             T     U   U    I         ||\n");
    printf("||        I    FFFF   O   O O   O  D  D             T     U   U    I         ||\n");
    printf("||        I    F      O   O O   O  D  D             T     U   U    I         ||\n");
    printf("||      IIIII  F       OOO   OOO   DDD              T      UUU   IIIII       ||\n");
    printf("||                                                                           ||\n");
    printf("===============================================================================\n");
    printf("||                                                                           ||\n");
    printf("||        Bem-vindo à sua experiência de delivery direto no terminal!        ||\n");
    printf("||                                                                           ||\n");
    printf("===============================================================================\n\n");
    printf("                         Selecione o modo de entrada:                          \n\n");
    printf("   +-----------------------------------------------------------------------+   \n\n");
}

void login_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                         A C E S S A R   C O N T A                       |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("              Bem-vindo de volta! Informe seus dados para entrar.          \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void login_error_ui()
{
    clearScreen();
    printf("+=========================================================================+\n");
    printf("|                                                                         |\n");
    printf("|                    *** E-mail ou senha incorretos! ***                  |\n");
    printf("|                                                                         |\n");
    printf("+=========================================================================+\n\n");
    printf("                   Verifique seus dados e tente novamente.\n");
    printf("  +---------------------------------------------------------------------+\n\n");
}

void cadastro_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                          N O V O   C A D A S T R O                      |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("           Por favor, preencha os campos abaixo para criar sua conta.      \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void code_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                 V E R I F I C A Ç Ã O   D E   C Ó D I G O               |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("     Para finalizar seu cadastro, enviamos um código de 5 dígitos para:    \n\n");
    printf("     E-mail: %s\n\n", cliente->email);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void endereco_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                I N F O R M A Ç Õ E S   D E   E N T R E G A              |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("     Para finalizar, precisamos do seu endereço para entrega dos pedidos   \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void modo_cliente_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                         M O D O   C L I E N T E                         |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?\n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
    printf("Endereço cadastrado: %s, %s, %d, CEP: %s\n", cliente->end.endereco, cliente->end.logradouro, cliente->end.numero, cliente->end.cep);
}

void modo_entregador_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                       M O D O   E N T R E G A D O R                     |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?\n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void modo_restaurante_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                       M O D O   R E S T A U R A N T E                   |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?\n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}