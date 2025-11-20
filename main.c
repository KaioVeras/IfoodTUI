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

struct Entregador
{
    char cpf[11];
    char tipo_veiculo[10];
    char placa[8];
    int idade;
};

struct Restaurante
{
    struct Endereco end;
    char nome_restaurante[50];
    char tipo_culinaria[30];
    char telefone_restaurante[20];
    char cnpj[18];
    char horario_abertura[6];
    char horario_fechamento[6];
    char horario_abertura_fds[6];
    char horario_fechamento_fds[6];
    char status;
    int cadastrado;
};

struct Cliente
{
    struct Endereco end;
    struct Restaurante rest;
    char nome[30];
    char cpf[11];
    char email[20];
    char telefone[20];
    char senha[20];
    int cadastro;
};

// Protótipos dos Procedimentos
void menu_ui();
void login_ui();
void cadastro_ui();
void clearScreen();
void limparBuffer();
void code_ui(struct Cliente *cliente);
void login_error_ui();
void endereco_ui();
void home_cliente_ui(struct Cliente *cliente);
void pedidos_cliente_ui();
void restaurante_dashboard_ui(struct Cliente *cliente);
void restaurante_pedidos_ui();
void restaurante_perfil_ui(struct Cliente *cliente);
void restaurante_configuracoes_ui();
void perfil_cliente_ui(struct Cliente *cliente);
void editar_perfil_cliente_ui(struct Cliente *cliente);
void modo_cliente_ui(struct Cliente *cliente);
void modo_entregador_ui(struct Cliente *cliente);
void modo_restaurante_ui(struct Cliente *cliente);
void modo_select_entrada_ui();
void configurarAcentuacao();
void status_restaurante_ui(struct Cliente *cliente);
void horario_funcionamento_ui(struct Cliente *cliente);
void dados_restaurante_ui();
void cadastro_restaurante_ui();
void dados_gerais_restaurante_ui(struct Cliente *cliente);
void login_nao_cadastrado_ui();

/// Protótipos das Funções
int menu(int opcao);
int menu_tipo();
int menu_cliente();
int menu_restaurante();
int menu_configuracoes_restaurante(struct Cliente *cliente);
int menu_perfil_cliente();
int menu_editar_perfil_cliente();
int cadastro(struct Cliente *cliente);
int cadastro_restaurante(struct Cliente *cliente);
int cadastro_entregador(struct Entregador *entregador, struct Cliente *cliente);
int logar(struct Cliente *cliente);
int le_valida_verificacao(struct Cliente *cliente);
int endereco(struct Endereco *end);

int main()
{
    configurarAcentuacao();
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    struct Cliente cliente;
    struct Restaurante restaurante;
    struct Entregador entregador;

    int opcao = 0, tipo = 0;

    // Inicializa a struct com valores vazios
    memset(&cliente, 0, sizeof(struct Cliente));
    cliente.rest.cadastrado = 0;

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
                printf("Usuário já cadastrado! Tente logar.\n");
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
                login_nao_cadastrado_ui();
                printf("\nPressione ENTER para continuar...");
                limparBuffer();
                getchar();
            }
            else
            {
                if (cliente.cadastro == 0)
                {
                    logar(&cliente);
                }

                do
                {
                    tipo = 0;
                    tipo = menu_tipo();

                    switch (tipo)
                    {
                    case 1:
                        modo_cliente_ui(&cliente);
                        limparBuffer();

                        do
                        {
                            tipo = 0;
                            tipo = menu_cliente();

                            switch (tipo)
                            {
                            case 1:
                                home_cliente_ui(&cliente);
                                limparBuffer();
                                getchar();
                                break;

                            case 2:
                                pedidos_cliente_ui();
                                limparBuffer();
                                getchar();
                                break;

                            case 3:
                                perfil_cliente_ui(&cliente);
                                limparBuffer();

                                do
                                {
                                    tipo = 0;
                                    tipo = menu_perfil_cliente();

                                    switch (tipo)
                                    {
                                    case 1:
                                        editar_perfil_cliente_ui(&cliente);
                                        limparBuffer();

                                        do
                                        {
                                            tipo = 0;
                                            tipo = menu_editar_perfil_cliente();

                                            switch (tipo)
                                            {
                                            case 1:
                                                int i = 0, ultimo_espaco = 0;
                                                printf("Insira o novo nome: ");
                                                scanf(" %[^\n]s", cliente.nome);

                                                for (i = 0; i < strlen(cliente.nome); i++)
                                                {
                                                    if (cliente.nome[i] == ' ')
                                                    {
                                                        ultimo_espaco = i + 1;
                                                    }
                                                }

                                                cliente.nome[0] = toupper(cliente.nome[0]);
                                                if (ultimo_espaco > 0)
                                                {
                                                    cliente.nome[ultimo_espaco] = toupper(cliente.nome[ultimo_espaco]);
                                                }

                                                printf("O nome foi alterado com sucesso!\n Novo nome: %s\n", cliente.nome);
                                                printf("\nPressione ENTER para continuar...");
                                                limparBuffer();
                                                getchar();
                                                break;

                                            case 2:
                                                printf("Insira o novo email: ");
                                                scanf(" %s", cliente.email);

                                                printf("O email foi alterado com sucesso!\n Novo email: %s\n", cliente.email);
                                                printf("\nPressione ENTER para continuar...");
                                                limparBuffer();
                                                getchar();
                                                break;

                                            case 3:
                                                printf("Insira o novo endereco: ");
                                                scanf(" %19[^\n]", cliente.end.endereco);

                                                printf("Insira o novo logradouro: ");
                                                scanf(" %9[^\n]", cliente.end.logradouro);

                                                printf("Insira o novo CEP: ");
                                                scanf(" %10s", cliente.end.cep);

                                                printf("Insira o novo numero: ");
                                                if (scanf(" %d", &cliente.end.numero) != 1)
                                                {
                                                    limparBuffer();
                                                    cliente.end.numero = 0;
                                                }

                                                printf("O endereco foi alterado com sucesso!\n Novo endereco: %s, %s, %d, CEP: %s\n", cliente.end.endereco, cliente.end.logradouro, cliente.end.numero, cliente.end.cep);
                                                printf("\nPressione ENTER para continuar...");
                                                limparBuffer();
                                                getchar();
                                                break;

                                            case 4:

                                                break;

                                            default:
                                                clearScreen();
                                                printf("Opcao invalida, tente novamente\n");
                                            }
                                        } while (tipo != 4);
                                        break;

                                    case 2:
                                        printf("Alterar Senha: ");
                                        scanf(" %s", cliente.senha);
                                        printf("Senha alterada com sucesso!\n");
                                        break;

                                    case 3:
                                        printf("Excluir Conta");
                                        break;

                                    case 4:

                                        break;

                                    default:
                                        clearScreen();
                                        printf("Opcao invalida, tente novamente\n");
                                    }
                                } while (tipo != 4);
                                break;

                            case 4:

                                break;
                            }
                        } while (tipo != 4);
                        break;

                    case 2:
                        modo_entregador_ui(&cliente);
                        limparBuffer();
                        getchar();
                        break;

                    case 3:
                        if (cliente.rest.cadastrado == 0)
                        {
                            cadastro_restaurante(&cliente);
                        }

                        modo_restaurante_ui(&cliente);

                        do
                        {
                            tipo = 0;
                            tipo = menu_restaurante();

                            switch (tipo)
                            {
                            case 1:
                                restaurante_dashboard_ui(&cliente);
                                limparBuffer();
                                getchar();
                                break;

                            case 2:
                                restaurante_pedidos_ui();
                                limparBuffer();
                                getchar();
                                break;

                            case 3:
                                restaurante_perfil_ui(&cliente);
                                limparBuffer();
                                getchar();
                                break;

                            case 4:
                                do
                                {
                                    restaurante_configuracoes_ui();

                                    tipo = 0;
                                    tipo = menu_configuracoes_restaurante(&cliente);

                                    switch (tipo)
                                    {
                                    case 1:
                                        dados_restaurante_ui();
                                        dados_gerais_restaurante_ui(&cliente);
                                        limparBuffer();
                                        getchar();
                                        break;

                                    case 2:
                                        status_restaurante_ui(&cliente);

                                        char resposta;
                                        int continuar = 1;

                                        while (continuar)
                                        {
                                            if (cliente.rest.status == 'a')
                                            {
                                                printf("O restaurante está ABERTO.\n");
                                                printf("Deseja fechar o restaurante? (s/n): ");
                                            }
                                            else
                                            {
                                                printf("O restaurante está FECHADO.\n");
                                                printf("Deseja abrir o restaurante? (s/n): ");
                                            }

                                            limparBuffer();
                                            scanf(" %c", &resposta);

                                            if (resposta == 's' || resposta == 'S')
                                            {
                                                // ** Opereção ternária para alternar o status - (condição) ? valor_se_verdadeiro : valor_se_falso **
                                                cliente.rest.status = (cliente.rest.status == 'a') ? 'f' : 'a';

                                                clearScreen();
                                                status_restaurante_ui(&cliente);

                                                if (cliente.rest.status == 'a')
                                                {
                                                    printf("Restaurante aberto com sucesso!\n");
                                                }
                                                else
                                                {
                                                    printf("Restaurante fechado com sucesso!\n");
                                                }
                                            }
                                            else if (resposta == 'n' || resposta == 'N')
                                            {
                                                continuar = 0;
                                            }
                                            else
                                            {
                                                printf("\nOpção inválida! Digite 's' ou 'n'.\n\n");
                                            }
                                        }

                                        printf("\nPressione ENTER para voltar...");
                                        limparBuffer();
                                        getchar();

                                        break;

                                    case 3:
                                        horario_funcionamento_ui(&cliente);
                                        limparBuffer();
                                        getchar();
                                        break;

                                    case 4:
                                        clearScreen();
                                        modo_restaurante_ui(&cliente);
                                        break;

                                    default:
                                        clearScreen();
                                        printf("Opcao invalida, tente novamente\n");
                                    }
                                } while (tipo != 4);
                                break;

                            case 5:

                                break;

                            default:
                                clearScreen();
                                printf("Opcao invalida, tente novamente\n");
                            }
                        } while (tipo != 5);

                        break;

                    case 4:

                        break;
                    }
                } while (tipo != 4);
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
int menu_tipo()
{
    int cont = 0;
    int tipo = 0;

    modo_select_entrada_ui();

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

// Função do menu do cliente
int menu_cliente()
{
    int cont = 0;
    int tipo = 0;

    printf("[1] >> Home\n");
    printf("[2] >> Pedidos\n");
    printf("[3] >> Perfil\n\n");
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

// Função do menu do restaurante
int menu_restaurante()
{
    int cont = 0;
    int tipo = 0;

    printf("[1] >> Dashboard\n");
    printf("[2] >> Pedidos\n");
    printf("[3] >> Perfil\n");
    printf("[4] >> Configurações\n\n");
    printf("[5] >> Voltar\n");

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
    } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

    return tipo;
}

int menu_perfil_cliente()
{
    int cont = 0;
    int tipo = 0;

    printf("[1] >> Editar Perfil\n");
    printf("[2] >> Alterar Senha\n");
    printf("[3] >> Excluir Conta\n\n");
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

int menu_editar_perfil_cliente()
{
    int cont = 0;
    int tipo = 0;

    printf("[1] >> Alterar Nome\n");
    printf("[2] >> Alterar Email\n");
    printf("[3] >> Alterar Endereço\n\n");
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

// Função do Menu configurações do restaurante
int menu_configuracoes_restaurante(struct Cliente *cliente)
{
    int cont = 0;
    int tipo = 0;

    printf("[1] >> Dados do Restaurante\n");
    printf("[2] >> Status do Restaurante\n");
    printf("[3] >> Horários de Funcionamento\n\n");

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

// Função de cadastro do restaurante
int cadastro_restaurante(struct Cliente *cliente)
{
    char nome[50];
    char tipo[30];
    char telefone[20];
    char cnpj[18];
    char abertura[6];
    char fechamento[6];
    char abertura_fds[6];
    char fechamento_fds[6];

    cadastro_restaurante_ui();

    printf("Digite o nome do restaurante: ");
    scanf(" %[^\n]s", nome);

    printf("Digite o tipo de culinária: ");
    scanf(" %[^\n]s", tipo);

    printf("Digite o telefone do restaurante: ");
    scanf(" %s", telefone);

    printf("Digite o endereço do restaurante: ");
    scanf(" %19[^\n]", cliente->rest.end.endereco);

    printf("Digite o logradouro do restaurante: ");
    scanf(" %9[^\n]", cliente->rest.end.logradouro);

    printf("Digite o CEP do restaurante: ");
    scanf(" %10s", cliente->rest.end.cep);

    printf("Digite o numero do restaurante: ");
    if (scanf(" %d", &cliente->rest.end.numero) != 1)
    {
        limparBuffer();
        cliente->rest.end.numero = 0;
    }

    printf("Digite o CNPJ: ");
    scanf(" %s", cnpj);

    printf("Digite o horário de abertura semana (HH:MM): ");
    scanf(" %s", abertura);

    printf("Digite o horário de fechamento semana(HH:MM): ");
    scanf(" %s", fechamento);

    printf("Digite o horário de abertura fim de semana (HH:MM): ");
    scanf(" %s", abertura_fds);

    printf("Digite o horário de fechamento fim de semana (HH:MM): ");
    scanf(" %s", fechamento_fds);

    strcpy(cliente->rest.nome_restaurante, nome);
    strcpy(cliente->rest.tipo_culinaria, tipo);
    strcpy(cliente->rest.telefone_restaurante, telefone);
    strcpy(cliente->rest.cnpj, cnpj);
    strcpy(cliente->rest.horario_abertura, abertura);
    strcpy(cliente->rest.horario_fechamento, fechamento);
    strcpy(cliente->rest.horario_abertura_fds, abertura_fds);
    strcpy(cliente->rest.horario_fechamento_fds, fechamento_fds);
    cliente->rest.status = 'a';
    cliente->rest.cadastrado = 1;

    printf("\nRestaurante cadastrado com sucesso!!\n");
    printf(">> Pressione ENTER para continuar...");
    limparBuffer();
    getchar();
    return 0;
}

// Função de cadastro cliente
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

// funçaõ cadastro entregador ------------
int cadastro_entregador(struct Entregador *entregador, struct Cliente *cliente)
{
    char tipo_veiculo[10];
    char placa[8];
    int idade = 0;
    char cpf[11];
    modo_entregador_ui(cliente);

    printf("Insira seu CPF: ");
    scanf("%[^\n]s", cpf);

    printf("Insira sua idade: ");
    scanf("%d", &idade);

    if (idade >= 18)
    {
        printf("Idade validada.");
    }
    else
    {
        printf("Você deve ser maior de 18 anos para ser um entregador!");
    }

    printf("Insira o tipo de veículo: ");
    scanf(" %[^\n]s", tipo_veiculo);

    tipo_veiculo[0] = toupper(tipo_veiculo[0]);

    if (!(strcmp(tipo_veiculo, "bicicleta")))
    {
        printf("Insira a placa: ");
        scanf("%[^\n]s", placa);
    }
    else
    {
        printf("Não tem placa para bicicleta.");
    }
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
    cliente->cadastro = 1;

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

    // Gera um número aleatório de 6 dígitos (100000 a 999999)
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

    if (scanf("%d", &codigo_inserido) != 1)
    {
        limparBuffer();
        codigo_inserido = 0;
    }

    do
    {
        if (codigo_inserido == codigo_correto)
        {
            printf("\nCódigo validado com sucesso.\n");
            printf(">> Pressione ENTER para continuar...");
            limparBuffer();
            getchar();
            break;
        }
        else
        {
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

    // Habilita sequências de escape ANSI no Windows 10+
    // HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // DWORD dwMode = 0;
    // GetConsoleMode(hOut, &dwMode);
    // dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    // SetConsoleMode(hOut, dwMode);

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
    printf("                   Verifique seus dados e tente novamente.                 \n");
    printf("  +---------------------------------------------------------------------+  \n\n");
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
    printf("     Para finalizar seu cadastro, enviamos um código de verificação para:  \n\n");
    printf("     E-mail: %s                                                             \n\n", cliente->email);
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

void modo_select_entrada_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                     S E L E Ç Ã O  D E  E N T R A D A                   |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?                          \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void modo_cliente_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                          M O D O   C L I E N T E                        |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?\n");
    printf("                Endereço: %s, %s, %d, CEP: %s  \n", cliente->end.endereco, cliente->end.logradouro, cliente->end.numero, cliente->end.cep);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void home_cliente_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                                H O M E                                  |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?                          \n\n");
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                     [BUSCAR] restaurante ou prato                       |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("|                   [Lanches] [Pizza] [Japonês] [Doces]                   |\n");
    printf("|              NOVO CUPOM: 10%% OFF em pedidos acima de R$ 50!            |\n\n");
    printf("| (1) - %s (4.8) - [taxa de entrega -> 15 reais]\n|Horário de funcionamento: %s as %s - Tempo de Entrega: 20-30 min\n| Tipo: %s\n", cliente->rest.nome_restaurante, cliente->rest.horario_abertura, cliente->rest.horario_fechamento, cliente->rest.tipo_culinaria);
}

void modo_entregador_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                       M O D O   E N T R E G A D O R                     |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?                          \n\n");
    printf("                  Endereço: %s, %s, %d, CEP: %s                            \n", cliente->end.endereco, cliente->end.logradouro, cliente->end.numero, cliente->end.cep);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void modo_restaurante_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                       M O D O   R E S T A U R A N T E                   |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         O que você deseja fazer?                          \n\n");
    printf("                 Endereço: %s, %s, %d, CEP: %s                             \n", cliente->rest.end.endereco, cliente->rest.end.logradouro, cliente->rest.end.numero, cliente->end.cep);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void pedidos_cliente_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                      P E D I D O S   C L I E N T E                      |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         Seus pedidos recentes:                            \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void perfil_cliente_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                       P E R F I L   D O   C L I E N T E                 |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                 Nome do Perfil:%s | Email:%s                              \n\n", cliente->nome, cliente->email);
    printf("  +---------------------------------------------------------------------+  \n\n");
    printf("Endrereço de Entrega: %s, %s, %d, CEP: %s                                  \n\n", cliente->end.endereco, cliente->end.logradouro, cliente->end.numero, cliente->end.cep);
}

void editar_perfil_cliente_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                 E D I T A R   P E R F I L   D O   C L I E N T E         |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                 Nome do Perfil:%s | Email:%s                              \n\n", cliente->nome, cliente->email);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void restaurante_dashboard_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                   R E S T A U R A N T E   D A S H B O A R D             |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                       Visão geral do restaurante: %s                      \n\n", cliente->rest.status == 'a' ? "Aberto" : "Fechado");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void restaurante_pedidos_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                   R E S T A U R A N T E   P E D I D O S                 |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                         Pedidos recebidos:                                \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void restaurante_perfil_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                 R E S T A U R A N T E   P E R F I L                     |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                 Nome do Restaurante:%s | Email:%s                         \n\n", cliente->nome, cliente->email);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void restaurante_configuracoes_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|               R E S T A U R A N T E   C O N F I G U R A Ç Õ E S         |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                     Ajuste as configurações do restaurante:               \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void status_restaurante_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                   S T A T U S   D O   R E S T A U R A N T E             |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                     Status atual do restaurante: %s                       \n\n", cliente->rest.status == 'a' ? "Aberto" : "Fechado");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void dados_restaurante_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                 D A D O S   D O   R E S T A U R A N T E                 |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("                       Informações do restaurante:                         \n");
}

void horario_funcionamento_ui(struct Cliente *cliente)
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|             H O R Á R I O   D E   F U N C I O N A M E N T O             |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("           Horário de funcionamento do restaurante: %s - %s                \n\n", cliente->rest.horario_abertura, cliente->rest.horario_fechamento);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void cadastro_restaurante_ui()
{
    clearScreen();
    printf("+-------------------------------------------------------------------------+\n");
    printf("|                                                                         |\n");
    printf("|                  C A D A S T R O   D O   R E S T A U R A N T E          |\n");
    printf("|                                                                         |\n");
    printf("+-------------------------------------------------------------------------+\n\n");
    printf("     Por favor, preencha os campos abaixo para cadastrar o restaurante     \n\n");
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void dados_gerais_restaurante_ui(struct Cliente *cliente)
{
    printf("  +---------------------------------------------------------------------+\n");
    printf("  | DADOS GERAIS                                                        |\n");
    printf("  +---------------------------------------------------------------------+\n");
    printf("  | Nome:       %-54s  |\n", cliente->rest.nome_restaurante);
    printf("  | CNPJ:       %-54s  |\n", cliente->rest.cnpj);
    printf("  | Telefone:   %-54s  |\n", cliente->rest.telefone_restaurante);
    printf("  +---------------------------------------------------------------------+\n\n");

    printf("  +---------------------------------------------------------------------+\n");
    printf("  | ENDEREÇO                                                            |\n");
    printf("  +---------------------------------------------------------------------+\n");
    printf("  | Endereço:   %-54s  |\n", cliente->rest.end.endereco);
    printf("  | Logradouro: %-54s  |\n", cliente->rest.end.logradouro);
    printf("  | Número:     %-54d  |\n", cliente->rest.end.numero);
    printf("  | CEP:        %-54s  |\n", cliente->rest.end.cep);
    printf("  +---------------------------------------------------------------------+\n\n");

    printf("  +---------------------------------------------------------------------+  \n");
    printf("  | HORÁRIOS DE FUNCIONAMENTO                                           |  \n");
    printf("  +---------------------------------------------------------------------+  \n");
    printf("  | Segunda - Sexta: %s - %-60s |  \n", cliente->rest.horario_abertura, cliente->rest.horario_fechamento);
    printf("  | Sábado - Domingo: %s - %-60s |  \n", cliente->rest.horario_abertura_fds, cliente->rest.horario_fechamento_fds);
    printf("  +---------------------------------------------------------------------+  \n\n");
}

void login_nao_cadastrado_ui()
{
    clearScreen();
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                           USUÁRIO NÃO CADASTRADO                             |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n\n");
    printf("              Por favor, realize o cadastro antes de fazer login.\n\n");
    printf("+------------------------------------------------------------------------------+\n\n");
}