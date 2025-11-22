#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Inclusao de bibliotecas especificas para Windows
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#endif

// Definicao das Structs
struct Endereco {
  char endereco[20];
  char logradouro[10];
  char cep[11];
  int numero;
};

struct Entregador {
  char cpf[11];
  char tipo_veiculo[10];
  char placa[8];
  int idade;
};

struct HorarioDia {
  char abertura[6];
  char fechamento[6];
};

struct Restaurante {
  struct Endereco end;
  char nome_restaurante[50];
  char tipo_culinaria[30];
  char telefone_restaurante[20];
  char cnpj[18];
  struct HorarioDia
      horarios[7]; /* 0=Seg, 1=Ter, 2=Qua, 3=Qui, 4=Sex, 5=Sab, 6=Dom */
  char horario_abertura[6];
  char horario_fechamento[6];
  char horario_abertura_fds[6];
  char horario_fechamento_fds[6];
  char status;
  int cadastrado;
};

struct Cliente {
  struct Endereco end;
  struct Restaurante rest;
  char nome[30];
  char cpf[11];
  char email[20];
  char telefone[20];
  char senha[20];
  int cadastro;
  int restaurantes_favoritos[10];
  int num_favoritos;
  int produtos_favoritos[50];
  int num_produtos_favoritos;
};

struct Produto {
  int id;
  char nome[50];
  char descricao[100];
  float preco;
  int quantidade;
  char categoria[30];
  int ativo;
};

struct ItemCarrinho {
  int id_produto;
  char nome_produto[50];
  float preco_unitario;
  int quantidade;
  float subtotal;
};

struct Carrinho {
  struct ItemCarrinho itens[50];
  int num_itens;
  float valor_total;
  float taxa_entrega;
};

struct Pedido {
  int id;
  char cpf_cliente[11];
  char nome_restaurante[50];
  struct ItemCarrinho itens[50];
  int num_itens;
  float valor_total;
  struct Endereco endereco_entrega;
  char forma_pagamento[20];
  char status[20];
  char data_hora[20];
};

// Prototipos dos Procedimentos
void menu_ui();
void login_ui();
void cadastro_ui();
void clearScreen();
void opcao_invalida_ui();
void limparBuffer();
void code_ui(struct Cliente *cliente);
void login_error_ui();
void endereco_ui();
void cadastro_feito_ui();
void home_cliente_ui(); // struct Cliente *cliente
void pedidos_cliente_ui(struct Pedido pedidos[], int num_pedidos,
                        struct Cliente *cliente);
void pagina_mcdonalds_ui();
void pagina_cocobambu_ui();
void pagina_dominos_ui();
void restaurante_dashboard_ui(struct Cliente *cliente);
void restaurante_pedidos_ui(struct Pedido pedidos[], int num_pedidos,
                            struct Cliente *cliente);
void restaurante_perfil_ui(struct Cliente *cliente);
void restaurante_configuracoes_ui();
void perfil_cliente_ui(struct Cliente *cliente);
void editar_perfil_cliente_ui(struct Cliente *cliente);
void alterar_senha_cliente_ui(struct Cliente *cliente);
void excluir_conta_cliente_ui();
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
void editar_horario_semana_ui();
void editar_horario_fds_ui();
void restaurante_dinamico_ui();
void cadastrar_produto_ui(struct Produto produtos[], int *num_produtos);
void listar_produtos_ui(struct Produto produtos[], int num_produtos);
void exibir_produtos_restaurante_ui(struct Produto produtos[],
                                    int num_produtos);
void adicionar_ao_carrinho_ui(struct Carrinho *carrinho,
                              struct Produto produtos[], int num_produtos);
void visualizar_carrinho_ui(struct Carrinho *carrinho);
void adicionar_produto_favorito_ui(struct Cliente *cliente,
                                   struct Produto produtos[], int num_produtos);
void listar_produtos_favoritos_ui(struct Cliente *cliente,
                                  struct Produto produtos[], int num_produtos);
int menu_carrinho();
void finalizar_compra_ui(struct Carrinho *carrinho, struct Cliente *cliente,
                         struct Pedido pedidos[], int *num_pedidos,
                         struct Produto produtos[], int num_produtos);
void adicionar_favorito_ui(struct Cliente *cliente, struct Produto produtos[]);
void listar_favoritos_ui(struct Cliente *cliente, struct Produto produtos[]);
void menu_gerenciar_produtos_ui(struct Produto produtos[], int *num_produtos);

/// Prototipos das Funcoes
int menu(int opcao);
int menu_tipo();
int menu_cliente();
int menu_restaurante();
int menu_configuracoes_restaurante(struct Cliente *cliente);
int menu_home();
int menu_perfil_cliente();
int menu_editar_perfil_cliente();
int menu_editar_horario_restaurante();
int cadastro(struct Cliente *cliente);
int cadastro_restaurante(struct Cliente *cliente);
int cadastro_entregador(struct Entregador *entregador, struct Cliente *cliente);
int logar(struct Cliente *cliente);
int enter_ui();
int le_valida_verificacao(struct Cliente *cliente);
char *alterar_senha(struct Cliente *cliente);
int excluir_conta(struct Cliente *cliente);
int endereco(struct Endereco *end);
int menu_mcdonalds();
int menu_cocobambu();
int menu_dominos();
int menu_gerenciar_produtos();
int menu_carrinho();
void inicializar_carrinho(struct Carrinho *carrinho);
void adicionar_item_carrinho(struct Carrinho *carrinho, int id_produto,
                             char nome[], float preco, int quantidade);
void remover_item_carrinho(struct Carrinho *carrinho, int index);
void limpar_carrinho(struct Carrinho *carrinho);
float calcular_total_carrinho(struct Carrinho *carrinho);

int main() {
  configurarAcentuacao();
  srand(time(NULL)); /* Inicializa o gerador de numeros aleatorios */

  struct Cliente cliente;
  struct Produto
      produtos[100]; /* Array para armazenar produtos do restaurante dinamico */
  struct Carrinho carrinho;
  struct Pedido pedidos[100]; /* Historico de pedidos */
  int num_produtos = 0;
  int num_pedidos = 0;

  int opcao = 0, tipo = 0, tipo_menu = 0, opcao_home = 0, opcao_restaurante = 0;

  // Inicializa a struct com valores vazios
  memset(&cliente, 0, sizeof(struct Cliente));
  cliente.rest.cadastrado = 0;
  cliente.num_favoritos = 0;
  cliente.num_produtos_favoritos = 0;

  // Inicializa o carrinho
  inicializar_carrinho(&carrinho);

  // Loop do menu
  do {
    menu_ui();
    opcao = menu(opcao);

    switch (opcao) {
    case 1:
      if (strlen(cliente.nome) != 0) {
        cadastro_feito_ui();
        tipo = enter_ui();
      } else {
        cadastro(&cliente);
        endereco(&cliente.end);
        le_valida_verificacao(&cliente);
        tipo = enter_ui();
      }
      break;

    case 2:
      if (strlen(cliente.nome) == 0) {
        clearScreen();
        login_nao_cadastrado_ui();
        tipo = enter_ui();
      } else {
        if (cliente.cadastro == 0) {
          logar(&cliente);
        }

        do {
          tipo_menu = 0;
          tipo_menu = menu_tipo();

          switch (tipo_menu) {
          case 1:
            do {
              modo_cliente_ui(&cliente);

              tipo = 0;
              tipo = menu_cliente();

              switch (tipo) {
              case 1:
                do {
                  home_cliente_ui(); // &cliente
                  // favoritos_ui(&cliente);
                  opcao_home = menu_home();

                  switch (opcao_home) {
                  case 1:
                    do {
                      pagina_mcdonalds_ui();
                      opcao_restaurante = menu_mcdonalds();
                    } while (opcao_restaurante != 5);
                    break;

                  case 2:
                    do {
                      pagina_cocobambu_ui();
                      opcao_restaurante = menu_cocobambu();
                    } while (opcao_restaurante != 5);
                    break;

                  case 3:
                    do {
                      pagina_dominos_ui();
                      opcao_restaurante = menu_dominos();
                    } while (opcao_restaurante != 5);
                    break;

                  case 4:
                    do {
                      exibir_produtos_restaurante_ui(produtos, num_produtos);

                      printf("\n[1] Adicionar ao Carrinho\n");
                      printf("[2] Adicionar aos Favoritos\n");
                      printf("[3] Ver Carrinho\n\n");
                      printf("[4] Voltar\n\n");

                      int opcao_rest_din;
                      printf("Entre o numero desejado: ");
                      if (scanf("%d", &opcao_rest_din) != 1) {
                        limparBuffer();
                        opcao_rest_din = 4;
                      }

                      switch (opcao_rest_din) {
                      case 1:
                        adicionar_ao_carrinho_ui(&carrinho, produtos,
                                                 num_produtos);
                        break;
                      case 2:
                        adicionar_produto_favorito_ui(&cliente, produtos,
                                                      num_produtos);
                        break;
                      case 3:
                        do {
                          visualizar_carrinho_ui(&carrinho);

                          /* Se carrinho esta vazio, sai direto */
                          if (carrinho.num_itens == 0) {
                            enter_ui();
                            break;
                          }

                          int opcao_carr = menu_carrinho();

                          switch (opcao_carr) {
                          case 1:
                            finalizar_compra_ui(&carrinho, &cliente, pedidos,
                                                &num_pedidos, produtos,
                                                num_produtos);
                            break;
                          case 2:
                            printf("\nDigite o numero do item para remover: ");
                            int item_remover;
                            if (scanf("%d", &item_remover) == 1) {
                              remover_item_carrinho(&carrinho,
                                                    item_remover - 1);
                            }
                            enter_ui();
                            break;
                          case 3:
                            limpar_carrinho(&carrinho);
                            printf("\n✓ Carrinho limpo!\n");
                            enter_ui();
                            break;
                          case 4:
                            break;
                          }

                          if (opcao_carr == 4 || carrinho.num_itens == 0)
                            break;

                        } while (1);
                        break;
                      case 4:
                        opcao_rest_din = 5;
                        break;
                      }

                      if (opcao_rest_din == 5)
                        break;

                    } while (1);
                    break;

                  case 5:

                    break;
                  }
                } while (opcao_home != 5);
                break;

              case 2:
                pedidos_cliente_ui(pedidos, num_pedidos, &cliente);
                enter_ui();
                break;

              case 3: {
                int opcao_perfil = 0;
                do {
                  perfil_cliente_ui(&cliente);

                  opcao_perfil = 0;
                  opcao_perfil = menu_perfil_cliente();

                  switch (opcao_perfil) {
                  case 1: {
                    int opcao_editar = 0;
                    do {
                      editar_perfil_cliente_ui(&cliente);

                      opcao_editar = 0;
                      opcao_editar = menu_editar_perfil_cliente();

                      switch (opcao_editar) {
                      case 1: {
                        int i = 0, ultimo_espaco = 0;
                        printf("Insira o novo nome: ");
                        scanf(" %[^\n]s", cliente.nome);
                        cliente.nome[0] = toupper(cliente.nome[0]);

                        for (i = 0; i < (int)strlen(cliente.nome); i++) {
                          if (cliente.nome[i] == ' ') {
                            ultimo_espaco = i + 1;
                          }
                        }

                        if (ultimo_espaco > 0) {
                          cliente.nome[ultimo_espaco] =
                              toupper(cliente.nome[ultimo_espaco]);
                        }

                        printf("O nome foi alterado com sucesso!\n Novo nome: "
                               "%s\n",
                               cliente.nome);
                        enter_ui();
                      } break;

                      case 2:
                        printf("Insira o novo email: ");
                        scanf(" %s", cliente.email);

                        printf("O email foi alterado com sucesso!\n Novo "
                               "email: %s\n",
                               cliente.email);
                        enter_ui();
                        break;

                      case 3:
                        printf("Insira o novo endereco: ");
                        scanf(" %19[^\n]", cliente.end.endereco);

                        printf("Insira o novo logradouro: ");
                        scanf(" %9[^\n]", cliente.end.logradouro);

                        printf("Insira o novo CEP: ");
                        scanf(" %10s", cliente.end.cep);

                        printf("Insira o novo numero: ");
                        if (scanf(" %d", &cliente.end.numero) != 1) {
                          limparBuffer();
                          cliente.end.numero = 0;
                        }

                        printf("O endereco foi alterado com sucesso!\n Novo "
                               "endereco: %s, %s, %d, CEP: %s\n",
                               cliente.end.endereco, cliente.end.logradouro,
                               cliente.end.numero, cliente.end.cep);
                        enter_ui();
                        break;

                      case 4:

                        break;

                      default:
                        opcao_invalida_ui();
                      }
                    } while (opcao_editar != 4);
                    break;
                  }

                  case 2:
                    alterar_senha_cliente_ui(&cliente);
                    alterar_senha(&cliente);

                    le_valida_verificacao(&cliente);

                    alterar_senha_cliente_ui(&cliente);
                    printf("Senha alterada com sucesso!\n");
                    enter_ui();
                    break;

                  // =====================================================
                  case 3: {
                    int opcao_fav = 0;
                    do {
                      clearScreen();
                      printf("+------------------------------------------------"
                             "-----------------------+\n");
                      printf("|                         FAVORITOS              "
                             "                       |\n");
                      printf("+------------------------------------------------"
                             "-----------------------+\n\n");
                      printf("[1] >> Ver Restaurantes Favoritos\n");
                      printf("[2] >> Ver Produtos Favoritos\n");
                      printf("[3] >> Adicionar Restaurante Favorito\n");
                      printf("[4] >> Adicionar Produto Favorito\n");
                      printf("[5] >> Voltar\n\n");

                      printf("Escolha: ");
                      if (scanf("%d", &opcao_fav) == 1) {
                        switch (opcao_fav) {
                        case 1:
                          listar_favoritos_ui(&cliente, produtos);
                          break;
                        case 2:
                          listar_produtos_favoritos_ui(&cliente, produtos,
                                                       num_produtos);
                          break;
                        case 3:
                          adicionar_favorito_ui(&cliente, produtos);
                          break;
                        case 4:
                          adicionar_produto_favorito_ui(&cliente, produtos,
                                                        num_produtos);
                          break;
                        case 5:
                          break;
                        default:
                          printf("\nOpcao invalida!\n");
                          enter_ui();
                        }
                      } else {
                        limparBuffer();
                        opcao_fav = 0;
                      }
                    } while (opcao_fav != 5);
                  } break;
                  case 4:
                    excluir_conta_cliente_ui();
                    if (excluir_conta(&cliente) == 1) {
                      opcao_perfil = 5;
                      tipo = 4;      // Sair do menu cliente tambem
                      tipo_menu = 4; // Sair do menu tipo usuario
                    }
                    enter_ui();
                    break;

                  case 5:

                    break;

                  default:
                    opcao_invalida_ui();
                  }
                } while (opcao_perfil != 5);
              } break;

              case 4:

                break;
              }
            } while (tipo != 4);
            break;

          case 2:
            modo_entregador_ui(&cliente);
            printf("Funcionalidade em desenvolvimento...\n");
            tipo = enter_ui();
            break;

          case 3:
            if (cliente.rest.cadastrado == 0) {
              cadastro_restaurante(&cliente);
            }

            modo_restaurante_ui(&cliente);

            do {
              clearScreen();
              modo_restaurante_ui(&cliente);

              tipo = 0;
              tipo = menu_restaurante();

              switch (tipo) {
              case 1:
                restaurante_dashboard_ui(&cliente);
                enter_ui();
                break;

              case 2:
                restaurante_pedidos_ui(pedidos, num_pedidos, &cliente);
                enter_ui();
                break;

              case 3:
                restaurante_perfil_ui(&cliente);
                enter_ui();
                break;

              case 4:
                do {
                  restaurante_configuracoes_ui();

                  tipo = 0;
                  tipo = menu_configuracoes_restaurante(&cliente);

                  switch (tipo) {
                  case 1:
                    dados_restaurante_ui();
                    dados_gerais_restaurante_ui(&cliente);
                    break;

                  case 2:
                    status_restaurante_ui(&cliente);

                    char resposta;
                    int continuar = 1;

                    while (continuar) {
                      if (cliente.rest.status == 'a') {
                        printf("O restaurante esta ABERTO.\n");
                        printf("Deseja fechar o restaurante? (s/n): ");
                      } else {
                        printf("O restaurante esta FECHADO.\n");
                        printf("Deseja abrir o restaurante? (s/n): ");
                      }

                      limparBuffer();
                      scanf(" %c", &resposta);

                      if (resposta == 's' || resposta == 'S') {
                        // ** Operacao ternaria para alternar o status -
                        // (condicao) ? valor_se_verdadeiro : valor_se_falso **
                        cliente.rest.status =
                            (cliente.rest.status == 'a') ? 'f' : 'a';

                        clearScreen();
                        status_restaurante_ui(&cliente);

                        if (cliente.rest.status == 'a') {
                          printf("Restaurante aberto com sucesso!\n");
                        } else {
                          printf("Restaurante fechado com sucesso!\n");
                        }
                      } else if (resposta == 'n' || resposta == 'N') {
                        continuar = 0;
                      } else {
                        printf("\nOpcao invalida! Digite 's' ou 'n'.\n\n");
                      }
                    }

                    tipo = enter_ui();
                    break;

                  case 3:
                    horario_funcionamento_ui(&cliente);

                    tipo = 0;
                    printf("\n+------------------------------------------------"
                           "+\n");
                    printf(
                        "| EDITAR HORARIOS                                |\n");
                    printf(
                        "+------------------------------------------------+\n");
                    printf(
                        "| [1] Segunda-feira                              |\n");
                    printf(
                        "| [2] Terca-feira                                |\n");
                    printf(
                        "| [3] Quarta-feira                               |\n");
                    printf(
                        "| [4] Quinta-feira                               |\n");
                    printf(
                        "| [5] Sexta-feira                                |\n");
                    printf(
                        "| [6] Sabado                                     |\n");
                    printf(
                        "| [7] Domingo                                    |\n");
                    printf(
                        "| [8] Editar todos os dias                       |\n");
                    printf(
                        "| [9] Voltar                                     |\n");
                    printf(
                        "+------------------------------------------------+\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &tipo);
                    limparBuffer();

                    if (tipo >= 1 && tipo <= 7) {
                      const char *dias[7] = {"Segunda-feira", "Terca-feira",
                                             "Quarta-feira",  "Quinta-feira",
                                             "Sexta-feira",   "Sabado",
                                             "Domingo"};
                      int dia = tipo - 1;

                      printf("\n+----------------------------------------------"
                             "--+\n");
                      printf("| EDITAR HORARIO - %s%-*s|\n", dias[dia],
                             (int)(32 - strlen(dias[dia])), "");
                      printf("+------------------------------------------------"
                             "+\n");
                      printf("Horario atual: %s - %s\n",
                             cliente.rest.horarios[dia].abertura,
                             cliente.rest.horarios[dia].fechamento);

                      printf("\nInsira o novo horario de abertura (HH:MM): ");
                      scanf(" %5s", cliente.rest.horarios[dia].abertura);

                      printf("Insira o novo horario de fechamento (HH:MM): ");
                      scanf(" %5s", cliente.rest.horarios[dia].fechamento);

                      printf("\nHorario de %s atualizado com sucesso!\n",
                             dias[dia]);
                      printf("Novo horario: %s - %s\n",
                             cliente.rest.horarios[dia].abertura,
                             cliente.rest.horarios[dia].fechamento);
                      enter_ui();
                    } else if (tipo == 8) {
                      printf("\n+----------------------------------------------"
                             "--+\n");
                      printf("| EDITAR TODOS OS HORARIOS                       "
                             "|\n");
                      printf("+------------------------------------------------"
                             "+\n");

                      printf("Insira o horario de abertura (HH:MM): ");
                      char abertura[6], fechamento[6];
                      scanf(" %5s", abertura);

                      printf("Insira o horario de fechamento (HH:MM): ");
                      scanf(" %5s", fechamento);

                      int d = 0;
                      for (d = 0; d < 7; d++) {
                        strcpy(cliente.rest.horarios[d].abertura, abertura);
                        strcpy(cliente.rest.horarios[d].fechamento, fechamento);
                      }

                      printf("\nTodos os horarios foram atualizados com "
                             "sucesso!\n");
                      printf("Novo horario: %s - %s\n", abertura, fechamento);
                      enter_ui();
                    }
                    break;

                  case 4:
                    menu_gerenciar_produtos_ui(produtos, &num_produtos);
                    break;

                  case 5:
                    break;
                  default:
                    opcao_invalida_ui();
                  }
                } while (tipo != 5);
                break;

              case 5:

                break;

              default:
                opcao_invalida_ui();
              }
            } while (tipo != 5);
            break;

          case 4:

            break;
          }
        } while (tipo_menu != 4);
      }
      break;

    case 3:
      clearScreen();
      printf("Programa Finalizado\n");
      break;

    default:
      opcao_invalida_ui();
    }
  } while (opcao != 3);
  return 0;
}

// Funcao do menu inicial
int menu(int opcao) {
  int cont = 0;

  printf("[1] >> Cadastrar\n");
  printf("[2] >> Logar\n");
  printf("[3] >> Sair\n\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }
    printf("Entre o numero desejado: ");
    if (scanf("%d", &opcao) != 1) {
      limparBuffer();
      opcao = 0;
    }
    cont++;
  } while (opcao != 3 && opcao != 1 && opcao != 2);

  return opcao;
}

// Funcao do menu do tipo de usuario
int menu_tipo() {
  int cont = 0;
  int tipo = 0;

  modo_select_entrada_ui();

  printf("[1] >> Cliente\n");
  printf("[2] >> Entregador\n");
  printf("[3] >> Restaurante\n\n");
  printf("[4] >> Voltar\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }
    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }
    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4);

  return tipo;
}

// Funcao do menu do cliente
int menu_cliente() {
  int cont = 0;
  int tipo = 0;

  printf("[1] >> Home\n");
  printf("[2] >> Pedidos\n");
  printf("[3] >> Perfil\n\n");
  printf("[4] >> Voltar\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4);

  return tipo;
}

// Funcao do menu do restaurante
int menu_restaurante() {
  int cont = 0;
  int tipo = 0;

  printf("[1] >> Dashboard\n");
  printf("[2] >> Pedidos\n");
  printf("[3] >> Perfil\n");
  printf("[4] >> Configuracoes\n\n");
  printf("[5] >> Voltar\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

  return tipo;
}

int menu_editar_horario_restaurante() {
  int cont = 0;
  int tipo = 0;

  printf("[1] >> Horario da semana (Seg-Sex)\n");
  printf("[2] >> Horario do final de semana (Sab-Dom)\n\n");

  printf("[3] >> Voltar\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3);

  return tipo;
}

int menu_perfil_cliente() {
  int cont = 0;
  int tipo = 0;

  printf("[1] >> Editar Perfil\n");
  printf("[2] >> Alterar Senha\n");
  printf("[3] >> Favoritos\n");
  printf("[4] >> Excluir Conta\n\n");
  printf("[5] >> Voltar\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

  return tipo;
}

int menu_home() {
  int cont = 0;
  int tipo = 0;

  printf(" +-------------------------------------------------------------------"
         "----+\n");
  printf(" |  [1]  McDonald's                                       * 4.5      "
         "    |\n");
  printf(" |       Lanches  -  30-40 min  -  R$ 5.99                           "
         "    |\n");
  printf(" +-------------------------------------------------------------------"
         "----+\n\n");

  printf(" +-------------------------------------------------------------------"
         "----+\n");
  printf(" |  [2]  Coco Bambu                                       * 4.8      "
         "    |\n");
  printf(" |       Frutos do Mar  -  50-60 min  -  R$ 12.00                    "
         "    |\n");
  printf(" +-------------------------------------------------------------------"
         "----+\n\n");

  printf(" +-------------------------------------------------------------------"
         "----+\n");
  printf(" |  [3]  Domino's Pizza                                   * 4.2      "
         "    |\n");
  printf(" |       Pizza  -  40-50 min  -  Gratis                              "
         "    |\n");
  printf(" +-------------------------------------------------------------------"
         "----+\n\n");

  printf(" +-------------------------------------------------------------------"
         "----+\n");
  printf(" |  [4]  Restaurante Dinamico                             * 5.0      "
         "    |\n");
  printf(" |       Variado  -  20-30 min  -  R$ 8.00                           "
         "    |\n");
  printf(" +-------------------------------------------------------------------"
         "----+\n\n");

  printf("[5] >> Voltar\n\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

  return tipo;
}

int menu_editar_perfil_cliente() {
  int cont = 0;
  int tipo = 0;

  printf("[1] >> Alterar Nome\n");
  printf("[2] >> Alterar Email\n");
  printf("[3] >> Alterar Endereco\n\n");
  printf("[4] >> Voltar\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4);

  return tipo;
}

int menu_mcdonalds() {
  int cont = 0;
  int tipo = 0;

  printf("   Hamburgueres\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [1]  Big Mac                                         +-------+ "
         "      |\n");
  printf("   |       Dois hamburgueres, alface, queijo especial      |       | "
         "      |\n");
  printf("   |       R$ 28.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [2]  Quarteirao com Queijo                           +-------+ "
         "      |\n");
  printf("   |       Hamburguer, queijo, picles, cebola e ketchup    |       | "
         "      |\n");
  printf("   |       R$ 26.50                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   Acompanhamentos\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [3]  Batata Frita Media                              +-------+ "
         "      |\n");
  printf("   |       Batatas crocantes e sequinhas                   |       | "
         "      |\n");
  printf("   |       R$ 12.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   Bebidas\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [4]  Coca-Cola 500ml                                 +-------+ "
         "      |\n");
  printf("   |       Refrigerante gelado                             |       | "
         "      |\n");
  printf("   |       R$ 7.50                                         | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   [5] >> Voltar\n\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

  return tipo;
}

int menu_cocobambu() {
  int cont = 0;
  int tipo = 0;

  printf("   Pratos Principais\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [1]  Camarao Internacional                           +-------+ "
         "      |\n");
  printf("   |       Camaroes ao molho de coco com arroz             |       | "
         "      |\n");
  printf("   |       R$ 89.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [2]  Lagosta Grelhada                                +-------+ "
         "      |\n");
  printf("   |       Lagosta inteira grelhada com manteiga           |       | "
         "      |\n");
  printf("   |       R$ 149.90                                       | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   Acompanhamentos\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [3]  Arroz de Coco                                   +-------+ "
         "      |\n");
  printf("   |       Arroz especial preparado com leite de coco      |       | "
         "      |\n");
  printf("   |       R$ 18.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   Bebidas\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [4]  Caipirinha de Limao                             +-------+ "
         "      |\n");
  printf("   |       Bebida refrescante com limao                    |       | "
         "      |\n");
  printf("   |       R$ 22.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   [5] >> Voltar\n\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

  return tipo;
}

int menu_dominos() {
  int cont = 0;
  int tipo = 0;

  printf("   Pizzas\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [1]  Pizza Pepperoni Grande                          +-------+ "
         "      |\n");
  printf("   |       Mucarela, pepperoni e oregano                  |       |  "
         "     |\n");
  printf("   |       R$ 54.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [2]  Pizza Margherita Grande                         +-------+ "
         "      |\n");
  printf("   |       Mucarela, tomate, manjericao e oregano         |       |  "
         "     |\n");
  printf("   |       R$ 49.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   Acompanhamentos\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [3]  Palitos de Queijo                               +-------+ "
         "      |\n");
  printf("   |       Palitos crocantes recheados com queijo          |       | "
         "      |\n");
  printf("   |       R$ 19.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   Bebidas\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  [4]  Refrigerante 2L                                 +-------+ "
         "      |\n");
  printf("   |       Coca-Cola, Guarana ou Fanta                     |       | "
         "      |\n");
  printf("   |       R$ 12.90                                        | [IMG] | "
         "      |\n");
  printf("   |                                                       |       | "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  printf("   [5] >> Voltar\n\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

  return tipo;
}

// Funcao do Menu configuracoes do restaurante
int menu_configuracoes_restaurante(struct Cliente *cliente) {
  (void)cliente; // Parametro nao utilizado no momento
  int cont = 0;
  int tipo = 0;

  printf("[1] >> Dados do Restaurante\n");
  printf("[2] >> Status do Restaurante\n");
  printf("[3] >> Horarios de Funcionamento\n");
  printf("[4] >> Gerenciar Produtos\n\n");

  printf("[5] >> Voltar\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &tipo) != 1) {
      limparBuffer();
      tipo = 0;
    }

    cont++;
  } while (tipo != 1 && tipo != 2 && tipo != 3 && tipo != 4 && tipo != 5);

  return tipo;
}

// Funcao de cadastro do restaurante
int cadastro_restaurante(struct Cliente *cliente) {
  char nome[50];
  char tipo[30];
  char telefone[20];
  char cnpj[18];
  char abertura[6];
  char fechamento[6];
  char abertura_fds[6];
  char fechamento_fds[6];
  int primeiro_espaco = 0, i = 0, cont = 0;
  int d = 0;

  cadastro_restaurante_ui();

  printf("Digite o nome do restaurante: ");
  scanf(" %[^\n]s", nome);
  nome[0] = toupper(nome[0]);

  printf("Digite o tipo de culinaria: ");
  scanf(" %[^\n]s", tipo);
  tipo[0] = toupper(tipo[0]);

  printf("Digite o telefone do restaurante: ");
  scanf(" %s", telefone);

  printf("Digite o endereco do restaurante: ");
  scanf(" %19[^\n]", cliente->rest.end.endereco);

  for (i = 0; i < (int)strlen(cliente->rest.end.endereco); i++) {
    if (cliente->rest.end.endereco[i] == ' ' && cont == 0) {
      primeiro_espaco = i;
      cont++;
    }
  }

  for (i = 0; i < primeiro_espaco; i++) {
    cliente->rest.end.endereco[i] = toupper(cliente->rest.end.endereco[i]);
  }

  printf("Digite o logradouro do restaurante: ");
  scanf(" %9[^\n]", cliente->rest.end.logradouro);

  printf("Digite o CEP do restaurante: ");
  scanf(" %10s", cliente->rest.end.cep);

  printf("Digite o numero do restaurante: ");
  if (scanf(" %d", &cliente->rest.end.numero) != 1) {
    limparBuffer();
    cliente->rest.end.numero = 0;
  }

  printf("Digite o CNPJ: ");
  scanf(" %s", cnpj);

  char *dias_semana[] = {"Segunda-feira", "Terca-feira", "Quarta-feira",
                         "Quinta-feira",  "Sexta-feira", "Sabado",
                         "Domingo"};

  printf("\n+------------------------------------------------------------------"
         "+\n");
  printf(
      "|          CADASTRO DE HORARIOS POR DIA DA SEMANA                  |\n");
  printf("+------------------------------------------------------------------+"
         "\n\n");

  for (d = 0; d < 7; d++) {
    printf("--- %s ---\n\n", dias_semana[d]);
    printf("Horario de abertura (HH:MM): ");
    scanf(" %5s", cliente->rest.horarios[d].abertura);

    printf("Horario de fechamento (HH:MM): ");
    scanf(" %5s", cliente->rest.horarios[d].fechamento);
    printf("\n");
  }

  /* Copia os horarios de segunda para os campos antigos (compatibilidade) */
  strcpy(cliente->rest.horario_abertura, cliente->rest.horarios[0].abertura);
  strcpy(cliente->rest.horario_fechamento,
         cliente->rest.horarios[0].fechamento);
  strcpy(cliente->rest.horario_abertura_fds,
         cliente->rest.horarios[5].abertura);
  strcpy(cliente->rest.horario_fechamento_fds,
         cliente->rest.horarios[5].fechamento);

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
  enter_ui();
  return 0;
}

// Funcao de cadastro cliente
int cadastro(struct Cliente *cliente) {
  char nome[50];
  char email[50];
  char senha[20];
  int i = 0, ultimo_espaco = 0;

  cadastro_ui();

  printf("Digite seu nome: ");
  scanf(" %[^\n]s", nome);

  for (i = 0; i < (int)strlen(nome); i++) {
    if (nome[i] == ' ') {
      ultimo_espaco = i + 1;
    }
  }

  nome[0] = toupper(nome[0]);
  if (ultimo_espaco > 0) {
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
  enter_ui();
  return 0;
}

// funcao cadastro entregador ------------
int cadastro_entregador(struct Entregador *entregador,
                        struct Cliente *cliente) {
  (void)entregador; // Parametro nao utilizado no momento
  char tipo_veiculo[10];
  char placa[8];
  int idade = 0;
  char cpf[11];
  modo_entregador_ui(cliente);

  printf("Insira seu CPF: ");
  scanf("%[^\n]s", cpf);

  printf("Insira sua idade: ");
  scanf("%d", &idade);

  if (idade >= 18) {
    printf("Idade validada.");
  } else {
    printf("Voce deve ser maior de 18 anos para ser um entregador!");
  }

  printf("Insira o tipo de veiculo: ");
  scanf(" %[^\n]s", tipo_veiculo);

  tipo_veiculo[0] = toupper(tipo_veiculo[0]);

  if (!(strcmp(tipo_veiculo, "bicicleta"))) {
    printf("Insira a placa: ");
    scanf("%[^\n]s", placa);
  } else {
    printf("Nao tem placa para bicicleta.");
  }

  return 0;
}

// Funcao de login
int logar(struct Cliente *cliente) {
  char email[50];
  char senha[20];

  login_ui();

  do {
    printf("Digite seu email: ");
    scanf(" %s", email);

    printf("Digite sua senha: ");
    scanf(" %s", senha);

    if (strcmp(email, cliente->email) != 0 ||
        strcmp(senha, cliente->senha) != 0) {
      login_error_ui();
      printf("Email ou senha incorretos! Tente novamente.\n");
    }
  } while (strcmp(email, cliente->email) != 0 ||
           strcmp(senha, cliente->senha) != 0);
  cliente->cadastro = 1;

  printf("\nLogin realizado com sucesso!!\n");
  enter_ui();
  return 0;
}

// Funcao de endereco
int endereco(struct Endereco *end) {
  endereco_ui();

  printf("Digite o endereco: ");
  scanf(" %19[^\n]", end->endereco);

  printf("Digite o logradouro: ");
  scanf(" %9[^\n]", end->logradouro);

  printf("Digite o CEP: ");
  scanf(" %10s", end->cep);

  printf("Digite o numero: ");
  if (scanf(" %d", &end->numero) != 1) {
    limparBuffer();
    end->numero = 0;
  }

  printf("\nEndereco cadastrado com sucesso!!\n");
  enter_ui();
  return 0;
}

char *alterar_senha(struct Cliente *cliente) {
  int cont = 0;
  char senha[20];
  strcpy(senha, cliente->senha);

  do {
    if (cont > 0) {
      printf("Senha incorreta! Tente novamente: ");
      scanf(" %s", senha);
    } else {
      printf("Insira a Senha atual para confirmacao: ");
      scanf(" %s", senha);
    }
    cont++;
  } while (strcmp(senha, cliente->senha) != 0);

  cont = 0;
  do {
    if (cont > 0) {
      printf("Senha igual a anterior! Tente novamente: ");
      scanf(" %s", cliente->senha);
    } else {
      printf("\nInsira Senha nova: ");
      scanf(" %s", cliente->senha);
    }
    cont++;
  } while (strcmp(senha, cliente->senha) == 0);

  return cliente->senha;
}

int excluir_conta(struct Cliente *cliente) {
  char delete_confirm;
  int cont = 0;
  char senha[20];

  printf("Tem certeza que deseja excluir sua "
         "conta? Essa acao e irreversivel. (s/n): ");
  scanf(" %c", &delete_confirm);

  if (delete_confirm == 's' || delete_confirm == 'S') {
    do {
      if (cont > 0) {
        printf("Senha incorreta! Tente novamente: ");
        scanf(" %19s", senha);
      } else {
        printf("\nInsira a Senha atual para confirmacao: ");
        scanf(" %19s", senha);
      }
      cont++;
    } while (strcmp(senha, cliente->senha) != 0);

    cliente->cadastro = 0;
    memset(cliente, 0, sizeof(struct Cliente));
    printf("\nConta excluida com sucesso!\n");
    return 1;
  } else {
    printf("\nOperacao cancelada. Sua conta nao foi excluida.\n");
  }
  return 0;
}

// Funcao de teste de codigo
int testecodigo(struct Cliente *cliente) {

  if (le_valida_verificacao(cliente)) {
    printf("\nAcesso Concedido. Bem-vindo ao sistema\n");
  } else {
    printf("Acesso Negado, tente novamente.\n");
  }

  return 0;
}

// Funcao para gerar codigo aleatorio
int gerar_codigo() {
  int codigo;

  // Gera um numero aleatorio de 6 digitos (100000 a 999999)
  codigo = 100000 + (rand() % 900000);

  return codigo;
}

// Funcao para ler e validar o codigo
int le_valida_verificacao(struct Cliente *cliente) {
  int codigo_correto = 0;
  codigo_correto = gerar_codigo();
  int codigo_inserido = 0;

  code_ui(cliente);
  printf("Insira o codigo (%d): ", codigo_correto);

  if (scanf("%d", &codigo_inserido) != 1) {
    limparBuffer();
    codigo_inserido = 0;
  }

  do {
    if (codigo_inserido == codigo_correto) {
      printf("\nCodigo validado com sucesso.\n");
      break;
    } else {
      printf("Codigo Invalido! Tente novamente (%d): ", codigo_correto);
      if (scanf("%d", &codigo_inserido) != 1) {
        limparBuffer();
        codigo_inserido = 0;
      }
    }
  } while (!(codigo_inserido == codigo_correto));

  return 0;
}

// Procedimento paar pausar a interface do usuario
int enter_ui() {
  printf("\n>> Pressione ENTER para continuar...");
  limparBuffer();
  getchar();
  return 0;
}

// Procedimento para limpar a tela de acordo com o sistema operacional
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Procedimento para limpar o buffer do teclado
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Procedimento para configurar a acentuacao
void configurarAcentuacao() {
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

// Procedimentos de Interface do Usuario (UI)
void menu_ui() {
  clearScreen();
  printf("====================================================================="
         "==========\n");
  printf("||                                                                   "
         "        ||\n");
  printf("||      IIIII  FFFFFF  OOO   OOO   DDD           TTTTTTT  U   U  "
         "IIIII       ||\n");
  printf("||        I    F      O   O O   O  D  D             T     U   U    I "
         "        ||\n");
  printf("||        I    FFFF   O   O O   O  D  D             T     U   U    I "
         "        ||\n");
  printf("||        I    F      O   O O   O  D  D             T     U   U    I "
         "        ||\n");
  printf("||      IIIII  F       OOO   OOO   DDD              T      UUU   "
         "IIIII       ||\n");
  printf("||                                                                   "
         "        ||\n");
  printf("====================================================================="
         "==========\n");
  printf("||                                                                   "
         "        ||\n");
  printf("||        Bem-vindo a sua experiencia de delivery direto no "
         "terminal!        ||\n");
  printf("||                                                                   "
         "        ||\n");
  printf("====================================================================="
         "==========\n\n");
  printf("                         Selecione o modo de entrada:                "
         "          \n\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+   \n\n");
}

void login_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                         A C E S S A R   C O N T A                  "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("              Bem-vindo de volta! Informe seus dados para entrar.    "
         "      \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void login_error_ui() {
  clearScreen();
  printf("+===================================================================="
         "=====+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                    *** E-mail ou senha incorretos! ***             "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+===================================================================="
         "=====+\n\n");
  printf("                   Verifique seus dados e tente novamente.           "
         "      \n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void cadastro_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                          N O V O   C A D A S T R O                 "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("           Por favor, preencha os campos abaixo para criar sua "
         "conta.      \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void cadastro_feito_ui() {
  clearScreen();
  printf("+===================================================================="
         "=====+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                U S U A R I O  C A D A S T R A D O                  "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+===================================================================="
         "=====+\n\n");
  printf("                 Usuario ja cadastrado! Tente logar.                 "
         "      \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void code_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                 V E R I F I C A C A O   D E   C O D I G O          "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("     Para finalizar seu cadastro, enviamos um codigo de verificacao "
         "para:  \n\n");
  printf("     E-mail: %s                                                      "
         "       \n\n",
         cliente->email);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void endereco_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                I N F O R M A C O E S   D E   E N T R E G A         "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("     Para finalizar, precisamos do seu endereco para entrega dos "
         "pedidos   \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void modo_select_entrada_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                     S E L E C A O  D E  E N T R A D A              "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                         O que voce deseja fazer?                    "
         "      \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void modo_cliente_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                          M O D O   C L I E N T E                   "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                         O que voce deseja fazer?\n");
  printf("                Endereco: %s, %s, %d, CEP: %s  \n",
         cliente->end.endereco, cliente->end.logradouro, cliente->end.numero,
         cliente->end.cep);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void home_cliente_ui() // struct Cliente *cliente
{
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                                H O M E                             "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                      O que voce esta procurando?                    "
         "      \n\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n");
}

void pagina_mcdonalds_ui() {
  clearScreen();
  printf("\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   |                          McDonald's                             "
         "      |\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  McDonald's                                                     "
         "      |\n");
  printf("   |  * 4.5 - 30-40 min - R$ 5.99                                    "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");
}

void pagina_cocobambu_ui() {
  clearScreen();
  printf("\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   |                          Coco Bambu                             "
         "      |\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  Coco Bambu                                                     "
         "      |\n");
  printf("   |  * 4.8 - 50-60 min - R$ 12.00                                   "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");
}

void pagina_dominos_ui() {
  clearScreen();
  printf("\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   |                        Domino's Pizza                           "
         "      |\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  Domino's Pizza                                                 "
         "      |\n");
  printf("   |  * 4.2 - 40-50 min - Gratis                                     "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");
}

void modo_entregador_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                       M O D O   E N T R E G A D O R                "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                         O que voce deseja fazer?                    "
         "      \n\n");
  printf("                  Endereco: %s, %s, %d, CEP: %s                      "
         "      \n",
         cliente->end.endereco, cliente->end.logradouro, cliente->end.numero,
         cliente->end.cep);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void modo_restaurante_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                       M O D O   R E S T A U R A N T E              "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                         O que voce deseja fazer?                    "
         "      \n\n");
  printf("                 Endereco: %s, %s, %d, CEP: %s                       "
         "      \n",
         cliente->rest.end.endereco, cliente->rest.end.logradouro,
         cliente->rest.end.numero, cliente->end.cep);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void pedidos_cliente_ui(struct Pedido pedidos[], int num_pedidos,
                        struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                      P E D I D O S   C L I E N T E                 "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");

  if (num_pedidos == 0) {
    printf("  Voce ainda nao fez nenhum pedido.\n\n");
    return;
  }

  int i, j;
  int pedidos_cliente = 0;

  for (i = 0; i < num_pedidos; i++) {
    /* Verifica se o pedido pertence ao cliente logado */
    if (strcmp(pedidos[i].cpf_cliente, cliente->cpf) == 0) {
      pedidos_cliente++;

      printf("  "
             "+----------------------------------------------------------------"
             "--+\n");
      printf("  | Pedido #%d - %-53s |\n", pedidos[i].id, pedidos[i].status);
      printf("  "
             "+----------------------------------------------------------------"
             "--+\n");
      printf("  | Restaurante: %-51s |\n", pedidos[i].nome_restaurante);
      printf("  | Data/Hora: %-53s |\n", pedidos[i].data_hora);
      printf("  | Itens:                                                       "
             "    |\n");

      for (j = 0; j < pedidos[i].num_itens; j++) {
        printf("  |   - %dx %-37s R$ %-8.2f |\n",
               pedidos[i].itens[j].quantidade, pedidos[i].itens[j].nome_produto,
               pedidos[i].itens[j].subtotal);
      }

      printf("  | Total: R$ %-57.2f |\n", pedidos[i].valor_total);
      printf("  | Forma de Pagamento: %-44s |\n", pedidos[i].forma_pagamento);
      printf("  | Endereco: %-54s |\n", pedidos[i].endereco_entrega.endereco);
      printf("  "
             "+----------------------------------------------------------------"
             "--+\n\n");
    }
  }

  if (pedidos_cliente == 0) {
    printf("  Voce ainda nao fez nenhum pedido.\n\n");
  }
}

void perfil_cliente_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                       P E R F I L   D O   C L I E N T E            "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                 Nome do Perfil:%s | Email:%s                        "
         "      \n\n",
         cliente->nome, cliente->email);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
  printf("Endereco de Entrega: %s, %s, %d, CEP: %s                            "
         "      \n\n",
         cliente->end.endereco, cliente->end.logradouro, cliente->end.numero,
         cliente->end.cep);
}

void editar_perfil_cliente_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                 E D I T A R   P E R F I L   D O   C L I E N T E    "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                 Nome do Perfil:%s | Email:%s                        "
         "      \n\n",
         cliente->nome, cliente->email);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void alterar_senha_cliente_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                 A L T E R A R   S E N H A   D O   C L I E N T E    "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                 Nome do Perfil:%s | Email:%s                        "
         "      \n\n",
         cliente->nome, cliente->email);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void excluir_conta_cliente_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|>>>>>>>>>>>> E X C L U I R   C O N T A   D O   C L I E N T E "
         "<<<<<<<<<<<<|\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("    Tem certeza que deseja excluir sua conta? Esta acao e "
         "irreversivel     \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void restaurante_dashboard_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "------+\n");
  printf("|                                                                    "
         "      |\n");
  printf("|                  R E S T A U R A N T E   D A S H B O A R D         "
         "      |\n");
  printf("|                                                                    "
         "      |\n");
  printf("+--------------------------------------------------------------------"
         "------+\n\n");

  // Status do restaurante
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  STATUS DO RESTAURANTE                                           "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Restaurante: %-54s |\n", cliente->rest.nome_restaurante);
  printf("  |  Status: %-59s |\n",
         cliente->rest.status == 'a' ? "Aberto" : "Fechado");
  printf("  |  Tipo de Culinaria: %-48s |\n", cliente->rest.tipo_culinaria);
  printf("  |  CNPJ: %-62s |\n", cliente->rest.cnpj);
  printf("  |  Telefone: %-59s |\n", cliente->rest.telefone_restaurante);
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  // Estatísticas do dia
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  ESTATISTICAS DO DIA                                             "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Pedidos Hoje: 12                                                "
         "    |\n");
  printf("  |  Pedidos Pendentes: 3                                            "
         "    |\n");
  printf("  |  Pedidos Concluidos: 9                                           "
         "    |\n");
  printf("  |  Faturamento Hoje: R$ 456,80                                     "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  // Estatísticas gerais
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  ESTATISTICAS GERAIS                                             "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Total de Pedidos: 247                                           "
         "    |\n");
  printf("  |  Avaliacao Media: 4.5/5.0                                        "
         "    |\n");
  printf("  |  Faturamento Total: R$ 8.934,50                                  "
         "    |\n");
  printf("  |  Clientes Ativos: 89                                             "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  // Horário de funcionamento
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  HORARIO DE FUNCIONAMENTO                                        "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");

  char *dias_dashboard[] = {"Segunda", "Terca",  "Quarta", "Quinta",
                            "Sexta",   "Sabado", "Domingo"};
  int i;
  for (i = 0; i < 7; i++) {
    printf("  |  %-10s: %s - %-48s |\n", dias_dashboard[i],
           cliente->rest.horarios[i].abertura,
           cliente->rest.horarios[i].fechamento);
  }
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");
}

void restaurante_pedidos_ui(struct Pedido pedidos[], int num_pedidos,
                            struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "------+\n");
  printf("|                                                                    "
         "      |\n");
  printf("|                  R E S T A U R A N T E   P E D I D O S             "
         "      |\n");
  printf("|                                                                    "
         "      |\n");
  printf("+--------------------------------------------------------------------"
         "------+\n\n");

  if (num_pedidos == 0) {
    printf("  "
           "+------------------------------------------------------------------"
           "----+\n");
    printf("  |  Nenhum pedido recebido ainda.                                 "
           "      |\n");
    printf("  "
           "+------------------------------------------------------------------"
           "----+\n\n");
    return;
  }

  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  PEDIDOS EM ANDAMENTO                                            "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  int i, j;
  float valor_total_pedidos = 0;

  for (i = 0; i < num_pedidos; i++) {
    printf("  "
           "+------------------------------------------------------------------"
           "----+\n");
    printf("  | Pedido #%d - %-58s |\n", pedidos[i].id, pedidos[i].status);
    printf("  "
           "+------------------------------------------------------------------"
           "----+\n");
    printf("  | Cliente: %-63s |\n", pedidos[i].cpf_cliente);
    printf("  | Horario: %-63s |\n", pedidos[i].data_hora);
    printf("  | Itens:                                                         "
           "      |\n");

    for (j = 0; j < pedidos[i].num_itens; j++) {
      printf("  |   - %dx %-42s R$ %-8.2f |\n", pedidos[i].itens[j].quantidade,
             pedidos[i].itens[j].nome_produto, pedidos[i].itens[j].subtotal);
    }

    printf("  | Total: R$ %-62.2f |\n", pedidos[i].valor_total);
    printf("  | Forma de Pagamento: %-50s |\n", pedidos[i].forma_pagamento);
    printf("  "
           "+------------------------------------------------------------------"
           "----+\n\n");

    valor_total_pedidos += pedidos[i].valor_total;
  }

  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  RESUMO                                                          "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Total de Pedidos Ativos: %-46d |\n", num_pedidos);
  printf("  |  Valor Total: R$ %-55.2f |\n", valor_total_pedidos);
  printf("  |  Tempo Medio de Preparo: 25 minutos                              "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");
}

void restaurante_perfil_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "------+\n");
  printf("|                                                                    "
         "      |\n");
  printf("|                  R E S T A U R A N T E   P E R F I L               "
         "      |\n");
  printf("|                                                                    "
         "      |\n");
  printf("+--------------------------------------------------------------------"
         "------+\n\n");

  // Informações Básicas
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  INFORMACOES BASICAS                                             "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Nome: %-64s |\n", cliente->rest.nome_restaurante);
  printf("  |  Email: %-63s |\n", cliente->email);
  printf("  |  Telefone: %-61s |\n", cliente->rest.telefone_restaurante);
  printf("  |  Tipo de Culinaria: %-52s |\n", cliente->rest.tipo_culinaria);
  printf("  |  CNPJ: %-63s |\n", cliente->rest.cnpj);
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  // Endereço
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  ENDERECO                                                        "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Rua: %-65s |\n", cliente->rest.end.endereco);
  printf("  |  Bairro: %-62s |\n", cliente->rest.end.logradouro);
  printf("  |  Numero: %-62d |\n", cliente->rest.end.numero);
  printf("  |  CEP: %-64s |\n", cliente->rest.end.cep);
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  // Horário de Funcionamento
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  HORARIO DE FUNCIONAMENTO                                        "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");

  char *dias_perfil[] = {"Segunda", "Terca",  "Quarta", "Quinta",
                         "Sexta",   "Sabado", "Domingo"};
  int j;
  for (j = 0; j < 7; j++) {
    printf("  |  %-10s: %s - %-48s |\n", dias_perfil[j],
           cliente->rest.horarios[j].abertura,
           cliente->rest.horarios[j].fechamento);
  }
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  // Status e Estatísticas
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  STATUS E ESTATISTICAS                                           "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Status Atual: %-58s |\n",
         cliente->rest.status == 'a' ? "Aberto" : "Fechado");
  printf("  |  Avaliacao Media: 4.5/5.0                                        "
         "    |\n");
  printf("  |  Total de Avaliacoes: 247                                        "
         "    |\n");
  printf("  |  Taxa de Aceitacao: 98%%                                         "
         "     |\n");
  printf("  |  Tempo Medio de Entrega: 35 minutos                              "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");

  // Informações Adicionais
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  INFORMACOES ADICIONAIS                                          "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n");
  printf("  |  Total de Produtos Cadastrados: 45                               "
         "    |\n");
  printf("  |  Total de Clientes: 156                                          "
         "    |\n");
  printf("  |  Faturamento Mensal: R$ 23.456,78                                "
         "    |\n");
  printf("  |  Data de Cadastro: 15/01/2024                                    "
         "    |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "--+\n\n");
}

void restaurante_configuracoes_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|               R E S T A U R A N T E   C O N F I G U R A C O E S    "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                     Ajuste as configuracoes do restaurante:         "
         "      \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void status_restaurante_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                   S T A T U S   D O   R E S T A U R A N T E        "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                     Status atual do restaurante: %s                 "
         "      \n\n",
         cliente->rest.status == 'a' ? "Aberto" : "Fechado");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void dados_restaurante_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                 D A D O S   D O   R E S T A U R A N T E            "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("                       Informacoes do restaurante:                   "
         "      \n");
}

void horario_funcionamento_ui(struct Cliente *cliente) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|             H O R A R I O   D E   F U N C I O N A M E N T O        "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");

  char *dias_horario[] = {"Segunda-feira", "Terca-feira", "Quarta-feira",
                          "Quinta-feira",  "Sexta-feira", "Sabado",
                          "Domingo"};
  int k;
  for (k = 0; k < 7; k++) {
    printf("  %-15s: %s - %s\n", dias_horario[k],
           cliente->rest.horarios[k].abertura,
           cliente->rest.horarios[k].fechamento);
  }

  printf("\n  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void cadastro_restaurante_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|                  C A D A S T R O   D O   R E S T A U R A N T E     "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
  printf("     Por favor, preencha os campos abaixo para cadastrar o "
         "restaurante     \n\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+  \n\n");
}

void dados_gerais_restaurante_ui(struct Cliente *cliente) {
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");
  printf("  | DADOS GERAIS                                                     "
         "   |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");
  printf("  | Nome:       %-54s  |\n", cliente->rest.nome_restaurante);
  printf("  | CNPJ:       %-54s  |\n", cliente->rest.cnpj);
  printf("  | Telefone:   %-54s  |\n", cliente->rest.telefone_restaurante);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n\n");

  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");
  printf("  | ENDERECO                                                         "
         "   |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");
  printf("  | Endereco:   %-54s  |\n", cliente->rest.end.endereco);
  printf("  | Logradouro: %-54s  |\n", cliente->rest.end.logradouro);
  printf("  | Numero:     %-54d  |\n", cliente->rest.end.numero);
  printf("  | CEP:        %-54s  |\n", cliente->rest.end.cep);
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n\n");

  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");
  printf("  | HORARIOS DE FUNCIONAMENTO                                        "
         "   |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");

  char *dias[] = {"Segunda", "Terca",  "Quarta", "Quinta",
                  "Sexta",   "Sabado", "Domingo"};
  int i;
  for (i = 0; i < 7; i++) {
    printf("  | %-15s: %s - %-42s |\n", dias[i],
           cliente->rest.horarios[i].abertura,
           cliente->rest.horarios[i].fechamento);
  }

  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n\n");

  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");
  printf("  | STATUS ATUAL                                                     "
         "   |\n");
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n");
  if (cliente->rest.status == 'a') {
    printf("  | >>>>>   A B E R T O   <<<<<                                    "
           "     |\n");
  } else {
    printf("  | >>>>>   F E C H A D O   <<<<<                                  "
           "     |\n");
  }
  printf("  "
         "+--------------------------------------------------------------------"
         "-+\n\n");

  enter_ui();
}

void login_nao_cadastrado_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "----------+\n");
  printf("|                                                                    "
         "          |\n");
  printf("|                           USUARIO NAO CADASTRADO                   "
         "          |\n");
  printf("|                                                                    "
         "          |\n");
  printf("+--------------------------------------------------------------------"
         "----------+\n\n");
  printf(
      "              Por favor, realize o cadastro antes de fazer login.\n\n");
  printf("+--------------------------------------------------------------------"
         "----------+\n\n");
}

void opcao_invalida_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "----------+\n");
  printf("|                                                                    "
         "          |\n");
  printf("|           O P C A O  I N V A L I D A !  T E N T E  N O V A M E N T "
         "E         |\n");
  printf("|                                                                    "
         "          |\n");
  printf("+--------------------------------------------------------------------"
         "----------+\n");
  enter_ui();
}

void editar_horario_semana_ui() {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|             E D I T A R   H O R A R I O   D A   S E M A N A        "
         "     |\n");
  printf("|                        ( S e g u n d a   -   S e x t a )           "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
}

void editar_horario_fds_ui() {
  printf("+--------------------------------------------------------------------"
         "-----+\n");
  printf("|                                                                    "
         "     |\n");
  printf("|    E D I T A R   H O R A R I O   D O   F I N A L   D E   S E M A N "
         "A    |\n");
  printf("|                    ( S a b a d o   -   D o m i n g o )             "
         "     |\n");
  printf("|                                                                    "
         "     |\n");
  printf("+--------------------------------------------------------------------"
         "-----+\n\n");
}

void restaurante_dinamico_ui() {
  clearScreen();
  printf("\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   |                        RESTAURANTE DINAMICO                     "
         "      |\n");
  printf("   |                                                                 "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");
  printf("\n");
  printf("                        EM DESENVOLVIMENTO                           "
         "     \n\n");
  printf("              Faz parte do modulo extra do projeto                   "
         "     \n\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");
}

// ==================== FUNCOES DO CARRINHO ====================

void inicializar_carrinho(struct Carrinho *carrinho) {
  carrinho->num_itens = 0;
  carrinho->valor_total = 0.0;
  carrinho->taxa_entrega = 0.0;
}

void adicionar_item_carrinho(struct Carrinho *carrinho, int id_produto,
                             char nome[], float preco, int quantidade) {
  if (carrinho->num_itens >= 50) {
    printf("Carrinho cheio! Nao e possivel adicionar mais itens.\n");
    return;
  }

  /* Verifica se o produto ja esta no carrinho */
  int i;
  for (i = 0; i < carrinho->num_itens; i++) {
    if (carrinho->itens[i].id_produto == id_produto) {
      carrinho->itens[i].quantidade += quantidade;
      carrinho->itens[i].subtotal =
          carrinho->itens[i].quantidade * carrinho->itens[i].preco_unitario;
      printf("\nQuantidade atualizada no carrinho!\n");
      return;
    }
  }

  // Adiciona novo item
  struct ItemCarrinho novo_item;
  novo_item.id_produto = id_produto;
  strcpy(novo_item.nome_produto, nome);
  novo_item.preco_unitario = preco;
  novo_item.quantidade = quantidade;
  novo_item.subtotal = preco * quantidade;

  carrinho->itens[carrinho->num_itens] = novo_item;
  carrinho->num_itens++;

  printf("\n✓ Produto adicionado ao carrinho!\n");
}

void remover_item_carrinho(struct Carrinho *carrinho, int index) {
  if (index < 0 || index >= carrinho->num_itens) {
    printf("Item invalido!\n");
    return;
  }

  /* Desloca os itens */
  int i;
  for (i = index; i < carrinho->num_itens - 1; i++) {
    carrinho->itens[i] = carrinho->itens[i + 1];
  }

  carrinho->num_itens--;
  printf("\n✓ Item removido do carrinho!\n");
}

void limpar_carrinho(struct Carrinho *carrinho) {
  carrinho->num_itens = 0;
  carrinho->valor_total = 0.0;
  carrinho->taxa_entrega = 0.0;
}

float calcular_total_carrinho(struct Carrinho *carrinho) {
  float total = 0.0;
  int i;
  for (i = 0; i < carrinho->num_itens; i++) {
    total += carrinho->itens[i].subtotal;
  }
  carrinho->valor_total = total + carrinho->taxa_entrega;
  return carrinho->valor_total;
}

// ==================== FUNCOES DE PRODUTOS ====================

void cadastrar_produto_ui(struct Produto produtos[], int *num_produtos) {
  if (*num_produtos >= 100) {
    printf("\nLimite de produtos atingido!\n");
    enter_ui();
    return;
  }

  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                        CADASTRAR NOVO PRODUTO                      "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  struct Produto novo;
  novo.id = *num_produtos + 1;

  printf("Nome do produto: ");
  scanf(" %49[^\n]", novo.nome);

  printf("Descricao: ");
  scanf(" %99[^\n]", novo.descricao);

  printf("Preco (R$): ");
  if (scanf("%f", &novo.preco) != 1) {
    limparBuffer();
    novo.preco = 0.0;
  }

  printf("Quantidade em estoque: ");
  if (scanf("%d", &novo.quantidade) != 1) {
    limparBuffer();
    novo.quantidade = 0;
  }

  printf("Categoria (Comida/Bebida/Acompanhamento/Sobremesa): ");
  scanf(" %29[^\n]", novo.categoria);

  novo.ativo = 1;

  produtos[*num_produtos] = novo;
  (*num_produtos)++;

  printf("\n✓ Produto cadastrado com sucesso! ID: %d\n", novo.id);
  enter_ui();
}

void listar_produtos_ui(struct Produto produtos[], int num_produtos) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                        PRODUTOS CADASTRADOS                        "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  if (num_produtos == 0) {
    printf("Nenhum produto cadastrado ainda.\n\n");
    enter_ui();
    return;
  }

  int i;
  for (i = 0; i < num_produtos; i++) {
    printf("ID: %d | %s %s\n", produtos[i].id,
           produtos[i].ativo ? "[✓]" : "[X]", produtos[i].nome);
    printf("   Categoria: %s | Preco: R$ %.2f | Estoque: %d\n",
           produtos[i].categoria, produtos[i].preco, produtos[i].quantidade);
    printf("   Descricao: %s\n", produtos[i].descricao);
    printf("-------------------------------------------------------------------"
           "----\n");
  }

  enter_ui();
}

void editar_produto_ui(struct Produto produtos[], int num_produtos) {
  if (num_produtos == 0) {
    printf("\nNenhum produto cadastrado para editar.\n");
    enter_ui();
    return;
  }

  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                        EDITAR PRODUTO                              "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  /* Lista os produtos */
  int i;
  for (i = 0; i < num_produtos; i++) {
    printf("[%d] %s - R$ %.2f (Estoque: %d) %s\n", produtos[i].id,
           produtos[i].nome, produtos[i].preco, produtos[i].quantidade,
           produtos[i].ativo ? "[Ativo]" : "[Inativo]");
  }

  int id_produto;
  printf("\nDigite o ID do produto para editar (0 para cancelar): ");
  if (scanf("%d", &id_produto) != 1) {
    limparBuffer();
    printf("ID invalido!\n");
    enter_ui();
    return;
  }

  if (id_produto == 0)
    return;

  /* Busca o produto */
  int encontrado = -1;
  for (i = 0; i < num_produtos; i++) {
    if (produtos[i].id == id_produto) {
      encontrado = i;
      break;
    }
  }

  if (encontrado == -1) {
    printf("\nProduto nao encontrado!\n");
    enter_ui();
    return;
  }

  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                    EDITANDO: %-20s                                 "
         "   |\n",
         produtos[encontrado].nome);
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  printf("Deixe em branco para manter o valor atual\n\n");

  /* Editar nome */
  printf("Nome atual: %s\n", produtos[encontrado].nome);
  printf("Novo nome: ");
  limparBuffer();
  char novo_nome[50];
  fgets(novo_nome, sizeof(novo_nome), stdin);
  novo_nome[strcspn(novo_nome, "\n")] = 0;
  if (strlen(novo_nome) > 0) {
    strcpy(produtos[encontrado].nome, novo_nome);
  }

  // Editar descricao
  printf("\nDescricao atual: %s\n", produtos[encontrado].descricao);
  printf("Nova descricao: ");
  char nova_desc[100];
  fgets(nova_desc, sizeof(nova_desc), stdin);
  nova_desc[strcspn(nova_desc, "\n")] = 0;
  if (strlen(nova_desc) > 0) {
    strcpy(produtos[encontrado].descricao, nova_desc);
  }

  // Editar preco
  printf("\nPreco atual: R$ %.2f\n", produtos[encontrado].preco);
  printf("Novo preco (0 para manter): ");
  float novo_preco;
  if (scanf("%f", &novo_preco) == 1 && novo_preco > 0) {
    produtos[encontrado].preco = novo_preco;
  }

  // Editar quantidade
  printf("\nEstoque atual: %d\n", produtos[encontrado].quantidade);
  printf("Novo estoque (-1 para manter): ");
  int nova_qtd;
  if (scanf("%d", &nova_qtd) == 1 && nova_qtd >= 0) {
    produtos[encontrado].quantidade = nova_qtd;
  }

  // Editar categoria
  printf("\nCategoria atual: %s\n", produtos[encontrado].categoria);
  printf("Nova categoria (Comida/Bebida/Acompanhamento/Sobremesa) ou Enter "
         "para manter: ");
  limparBuffer();
  char nova_cat[30];
  fgets(nova_cat, sizeof(nova_cat), stdin);
  nova_cat[strcspn(nova_cat, "\n")] = 0;
  if (strlen(nova_cat) > 0) {
    strcpy(produtos[encontrado].categoria, nova_cat);
  }

  printf("\n✓ Produto atualizado com sucesso!\n");
  enter_ui();
}

void ativar_desativar_produto_ui(struct Produto produtos[], int num_produtos) {
  if (num_produtos == 0) {
    printf("\nNenhum produto cadastrado.\n");
    enter_ui();
    return;
  }

  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                   ATIVAR/DESATIVAR PRODUTO                         "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  /* Lista os produtos */
  int i;
  for (i = 0; i < num_produtos; i++) {
    printf("[%d] %s - %s\n", produtos[i].id, produtos[i].nome,
           produtos[i].ativo ? "[ATIVO]" : "[INATIVO]");
  }

  int id_produto;
  printf("\nDigite o ID do produto (0 para cancelar): ");
  if (scanf("%d", &id_produto) != 1) {
    limparBuffer();
    printf("ID invalido!\n");
    enter_ui();
    return;
  }

  if (id_produto == 0)
    return;

  /* Busca o produto */
  int encontrado = -1;
  for (i = 0; i < num_produtos; i++) {
    if (produtos[i].id == id_produto) {
      encontrado = i;
      break;
    }
  }

  if (encontrado == -1) {
    printf("\nProduto nao encontrado!\n");
    enter_ui();
    return;
  }

  /* Alterna o status */
  produtos[encontrado].ativo = !produtos[encontrado].ativo;

  printf("\n✓ Produto '%s' agora esta: %s\n", produtos[encontrado].nome,
         produtos[encontrado].ativo ? "ATIVO" : "INATIVO");
  enter_ui();
}

int menu_gerenciar_produtos() {
  int opcao;
  int cont = 0;

  printf("\n[1] >> Cadastrar Produto\n");
  printf("[2] >> Listar Produtos\n");
  printf("[3] >> Editar Produto\n");
  printf("[4] >> Ativar/Desativar Produto\n\n");
  printf("[5] >> Voltar\n\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &opcao) != 1) {
      limparBuffer();
      opcao = 0;
    }

    cont++;
  } while (opcao < 1 || opcao > 5);

  return opcao;
}

void menu_gerenciar_produtos_ui(struct Produto produtos[], int *num_produtos) {
  int opcao;

  do {
    clearScreen();
    printf("+------------------------------------------------------------------"
           "-----+\n");
    printf("|                         GERENCIAR PRODUTOS                       "
           "     |\n");
    printf("+------------------------------------------------------------------"
           "-----+\n");

    opcao = menu_gerenciar_produtos();

    switch (opcao) {
    case 1:
      cadastrar_produto_ui(produtos, num_produtos);
      break;

    case 2:
      listar_produtos_ui(produtos, *num_produtos);
      break;

    case 3:
      editar_produto_ui(produtos, *num_produtos);
      break;

    case 4:
      ativar_desativar_produto_ui(produtos, *num_produtos);
      break;

    case 5:
      break;
    }

  } while (opcao != 5);
}

// ==================== FUNCOES DE EXIBICAO E COMPRA ====================

void exibir_produtos_restaurante_ui(struct Produto produtos[],
                                    int num_produtos) {
  clearScreen();
  printf("\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |                         RESTAURANTE DINAMICO                    "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n");
  printf("   |  * 5.0 - 20-30 min - R$ 8.00                                    "
         "      |\n");
  printf("   "
         "+--------------------------------------------------------------------"
         "---+\n\n");

  if (num_produtos == 0) {
    printf("   Nenhum produto cadastrado ainda.\n\n");
    return;
  }

  char categorias[10][30];
  int num_categorias = 0;

  /* Identifica categorias unicas */
  int i, j;
  for (i = 0; i < num_produtos; i++) {
    if (!produtos[i].ativo)
      continue;

    int encontrou = 0;
    for (j = 0; j < num_categorias; j++) {
      if (strcmp(categorias[j], produtos[i].categoria) == 0) {
        encontrou = 1;
        break;
      }
    }

    if (!encontrou) {
      strcpy(categorias[num_categorias], produtos[i].categoria);
      num_categorias++;
    }
  }

  /* Exibe produtos por categoria */
  int cat;
  for (cat = 0; cat < num_categorias; cat++) {
    printf("   %s\n", categorias[cat]);

    for (i = 0; i < num_produtos; i++) {
      if (produtos[i].ativo &&
          strcmp(produtos[i].categoria, categorias[cat]) == 0) {
        printf("   "
               "+--------------------------------------------------------------"
               "---------+\n");
        printf("   |  [%d]  %-57s       |\n", produtos[i].id, produtos[i].nome);
        printf("   |       %-59s     |\n", produtos[i].descricao);
        printf("   |       R$ %.2f  -  Estoque: %d                             "
               "           |\n",
               produtos[i].preco, produtos[i].quantidade);
        printf("   "
               "+--------------------------------------------------------------"
               "---------+\n\n");
      }
    }
  }
}

void adicionar_ao_carrinho_ui(struct Carrinho *carrinho,
                              struct Produto produtos[], int num_produtos) {
  clearScreen();

  if (num_produtos == 0) {
    printf("\nNenhum produto disponivel para adicionar.\n");
    enter_ui();
    return;
  }

  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                    ADICIONAR AO CARRINHO                           "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  printf("Produtos disponíveis:\n\n");

  /* Lista os produtos disponíveis */
  int i;
  for (i = 0; i < num_produtos; i++) {
    if (produtos[i].ativo) {
      printf("   [ID: %d] %s\n", produtos[i].id, produtos[i].nome);
      printf("   R$ %.2f | Estoque: %d\n", produtos[i].preco,
             produtos[i].quantidade);
      printf("   %s\n", produtos[i].descricao);
      printf("   "
             "-----------------------------------------------------------------"
             "-----\n");
    }
  }

  int id_produto, quantidade;

  printf("\nDigite o ID do produto: ");
  if (scanf("%d", &id_produto) != 1) {
    limparBuffer();
    printf("ID invalido!\n");
    enter_ui();
    return;
  }

  /* Busca o produto */
  int encontrado = -1;
  for (i = 0; i < num_produtos; i++) {
    if (produtos[i].id == id_produto && produtos[i].ativo) {
      encontrado = i;
      break;
    }
  }

  if (encontrado == -1) {
    printf("\nProduto nao encontrado ou indisponivel!\n");
    enter_ui();
    return;
  }

  printf("Digite a quantidade: ");
  if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
    limparBuffer();
    printf("Quantidade invalida!\n");
    enter_ui();
    return;
  }

  if (quantidade > produtos[encontrado].quantidade) {
    printf("\nEstoque insuficiente! Disponivel: %d\n",
           produtos[encontrado].quantidade);
    enter_ui();
    return;
  }

  adicionar_item_carrinho(carrinho, produtos[encontrado].id,
                          produtos[encontrado].nome, produtos[encontrado].preco,
                          quantidade);
  enter_ui();
}

void visualizar_carrinho_ui(struct Carrinho *carrinho) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                         MEU CARRINHO                               "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  if (carrinho->num_itens == 0) {
    printf("Carrinho vazio.\n\n");
    return;
  }

  int i;
  for (i = 0; i < carrinho->num_itens; i++) {
    printf("[%d] %s\n", i + 1, carrinho->itens[i].nome_produto);
    printf("    R$ %.2f x %d = R$ %.2f\n", carrinho->itens[i].preco_unitario,
           carrinho->itens[i].quantidade, carrinho->itens[i].subtotal);
    printf("-------------------------------------------------------------------"
           "----\n");
  }

  float total = calcular_total_carrinho(carrinho);
  printf("\nSubtotal: R$ %.2f\n", total - carrinho->taxa_entrega);
  printf("Taxa de Entrega: R$ %.2f\n", carrinho->taxa_entrega);
  printf("TOTAL: R$ %.2f\n\n", total);
}

int menu_carrinho() {
  int opcao;
  int cont = 0;

  printf("[1] >> Finalizar Compra\n");
  printf("[2] >> Remover Item\n");
  printf("[3] >> Limpar Carrinho\n\n");
  printf("[4] >> Voltar\n\n");

  do {
    if (cont > 0) {
      printf("Opcao invalida! Tente novamente: ");
    }

    printf("Entre o numero desejado: ");
    if (scanf("%d", &opcao) != 1) {
      limparBuffer();
      opcao = 0;
    }

    cont++;
  } while (opcao < 1 || opcao > 4);

  return opcao;
}

void finalizar_compra_ui(struct Carrinho *carrinho, struct Cliente *cliente,
                         struct Pedido pedidos[], int *num_pedidos,
                         struct Produto produtos[], int num_produtos) {
  (void)num_produtos; // Parametro usado indiretamente no loop de atualizacao de
                      // estoque

  if (carrinho->num_itens == 0) {
    printf("\nCarrinho vazio! Adicione produtos antes de finalizar.\n");
    enter_ui();
    return;
  }

  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                      FINALIZAR COMPRA                              "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  // Mostra resumo
  visualizar_carrinho_ui(carrinho);

  // Confirmacao de endereco
  printf("\nEndereco de entrega:\n");
  printf("%s, %s, %d - CEP: %s\n\n", cliente->end.endereco,
         cliente->end.logradouro, cliente->end.numero, cliente->end.cep);

  // Forma de pagamento
  char forma_pagamento[20];
  printf("Forma de pagamento:\n");
  printf("[1] Dinheiro\n");
  printf("[2] Cartao de Credito\n");
  printf("[3] Cartao de Debito\n");
  printf("[4] PIX\n\n");

  int opcao_pag;
  printf("Escolha: ");
  if (scanf("%d", &opcao_pag) != 1) {
    limparBuffer();
    printf("Opcao invalida!\n");
    enter_ui();
    return;
  }

  switch (opcao_pag) {
  case 1:
    strcpy(forma_pagamento, "Dinheiro");
    break;
  case 2:
    strcpy(forma_pagamento, "Cartao Credito");
    break;
  case 3:
    strcpy(forma_pagamento, "Cartao Debito");
    break;
  case 4:
    strcpy(forma_pagamento, "PIX");
    break;
  default:
    strcpy(forma_pagamento, "Nao informado");
  }

  // Confirmacao final
  char confirmar;
  printf("\nConfirmar pedido? (s/n): ");
  scanf(" %c", &confirmar);

  if (confirmar == 's' || confirmar == 'S') {
    // Cria o pedido
    struct Pedido novo_pedido;
    novo_pedido.id = *num_pedidos + 1;
    strcpy(novo_pedido.cpf_cliente, cliente->cpf);
    strcpy(novo_pedido.nome_restaurante, "Restaurante Dinamico");

    int i;
    for (i = 0; i < carrinho->num_itens; i++) {
      novo_pedido.itens[i] = carrinho->itens[i];
    }

    novo_pedido.num_itens = carrinho->num_itens;
    novo_pedido.valor_total = carrinho->valor_total;
    novo_pedido.endereco_entrega = cliente->end;
    strcpy(novo_pedido.forma_pagamento, forma_pagamento);
    strcpy(novo_pedido.status, "Preparando");
    strcpy(novo_pedido.data_hora, "21/11/2025 10:30");

    pedidos[*num_pedidos] = novo_pedido;
    (*num_pedidos)++;

    printf("\n✓ Pedido realizado com sucesso!\n");
    printf("Numero do pedido: #%d\n", novo_pedido.id);
    printf("Status: %s\n\n", novo_pedido.status);

    for (i = 0; i < carrinho->num_itens; i++) {
      int id_produto = carrinho->itens[i].id_produto;
      int qtd_comprada = carrinho->itens[i].quantidade;

      int j;
      for (j = 0; j < 100; j++) {
        if (produtos[j].id == id_produto) {
          produtos[j].quantidade -= qtd_comprada;
          break;
        }
      }
    }

    limpar_carrinho(carrinho);
  } else {
    printf("\nPedido cancelado.\n");
  }

  enter_ui();
}

// ==================== FUNCOES DE FAVORITOS ====================

void adicionar_favorito_ui(struct Cliente *cliente, struct Produto produtos[]) {
  int i;
  int opcao;

  if (cliente->num_favoritos >= 10) {
    printf("\nLimite de favoritos atingido!\n");
    enter_ui();
    return;
  }

  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                   ADICIONAR RESTAURANTE FAVORITO                   "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");
  printf("[1] Mc Donald`s\n");
  printf("[2] Coco Bambu\n");
  printf("[3] Domino's Pizza\n");
  printf("[4] %s\n\n", cliente->rest.nome_restaurante);
  printf("Escolha: ");
  if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
    limparBuffer();
    printf("Opcao invalida!\n");
    enter_ui();
    return;
  }

  /* Verifica se ja esta nos favoritos */
  for (i = 0; i < cliente->num_favoritos; i++) {
    if (cliente->restaurantes_favoritos[i] == opcao) {
      printf("\nRestaurante ja esta nos favoritos!\n");
      enter_ui();
      return;
    }
  }

  cliente->restaurantes_favoritos[cliente->num_favoritos] = opcao;
  cliente->num_favoritos++;

  printf("\n✓ Restaurante adicionado aos favoritos!\n");
  enter_ui();
}

void listar_favoritos_ui(struct Cliente *cliente, struct Produto produtos[]) {
  int i;
  (void)produtos; /* Parametro nao utilizado */

  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                              FAVORITOS                             "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  if (cliente->num_favoritos == 0) {
    printf("Nenhum item favorito ainda.\n\n");
    enter_ui();
    return;
  }

  char *nomes[] = {"", "Mc Donald`s", "Coco Bambu", "Domino's Pizza",
                   "Restaurante Dinamico"};
  for (i = 0; i < cliente->num_favoritos; i++) {
    int id = cliente->restaurantes_favoritos[i];
    printf("[%d] %s\n", i + 1, nomes[id]);
  }

  printf("\n");
  enter_ui();
}

// ==================== FUNCOES DE FAVORITOS DE PRODUTOS ====================

void adicionar_produto_favorito_ui(struct Cliente *cliente,
                                   struct Produto produtos[],
                                   int num_produtos) {
  clearScreen();

  if (num_produtos == 0) {
    printf("\nNenhum produto disponivel.\n");
    enter_ui();
    return;
  }

  if (cliente->num_produtos_favoritos >= 50) {
    printf("\nLimite de produtos favoritos atingido!\n");
    enter_ui();
    return;
  }

  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                    ADICIONAR PRODUTO AOS FAVORITOS                 "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  printf("Produtos disponíveis:\n\n");

  int i;
  for (i = 0; i < num_produtos; i++) {
    if (produtos[i].ativo) {
      printf("   [ID: %d] %s\n", produtos[i].id, produtos[i].nome);
      printf("   R$ %.2f - %s\n", produtos[i].preco, produtos[i].descricao);
      printf("   "
             "-----------------------------------------------------------------"
             "-----\n");
    }
  }

  int id_produto;
  printf("\n[0] Voltar\n\n");
  printf("Digite o ID do produto para adicionar aos favoritos (ou 0 para "
         "voltar): ");
  if (scanf("%d", &id_produto) != 1) {
    limparBuffer();
    printf("ID invalido!\n");
    enter_ui();
    return;
  }

  if (id_produto == 0) {
    return;
  }

  /* Busca o produto */
  int encontrado = -1;
  for (i = 0; i < num_produtos; i++) {
    if (produtos[i].id == id_produto && produtos[i].ativo) {
      encontrado = i;
      break;
    }
  }

  if (encontrado == -1) {
    printf("\nProduto nao encontrado ou indisponivel!\n");
    enter_ui();
    return;
  }

  /* Verifica se ja esta nos favoritos */
  for (i = 0; i < cliente->num_produtos_favoritos; i++) {
    if (cliente->produtos_favoritos[i] == id_produto) {
      printf("\nProduto ja esta nos favoritos!\n");
      enter_ui();
      return;
    }
  }

  cliente->produtos_favoritos[cliente->num_produtos_favoritos] = id_produto;
  cliente->num_produtos_favoritos++;

  printf("\n+ Produto '%s' adicionado aos favoritos!\n",
         produtos[encontrado].nome);
  enter_ui();
}

void listar_produtos_favoritos_ui(struct Cliente *cliente,
                                  struct Produto produtos[], int num_produtos) {
  clearScreen();
  printf("+--------------------------------------------------------------------"
         "---+\n");
  printf("|                        PRODUTOS FAVORITOS                          "
         "   |\n");
  printf("+--------------------------------------------------------------------"
         "---+\n\n");

  if (cliente->num_produtos_favoritos == 0) {
    printf("Nenhum produto favorito ainda.\n\n");
    enter_ui();
    return;
  }

  printf("Seus produtos favoritos:\n\n");

  int i, j;
  for (i = 0; i < cliente->num_produtos_favoritos; i++) {
    int id_produto = cliente->produtos_favoritos[i];

    /* Busca o produto no array */
    for (j = 0; j < num_produtos; j++) {
      if (produtos[j].id == id_produto) {
        printf("   [%d] %s\n", i + 1, produtos[j].nome);
        printf("   R$ %.2f - %s\n", produtos[j].preco, produtos[j].descricao);
        printf("   Estoque: %d unidades\n", produtos[j].quantidade);
        printf("   "
               "---------------------------------------------------------------"
               "-------\n");
        break;
      }
    }
  }

  printf("\n");
  enter_ui();
}