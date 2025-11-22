#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Inclusão de bibliotecas específicas para Windows
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#include <windows.h>
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
       int restaurantes_favoritos[10];
       int num_favoritos;
};

struct Produto
{
       int id;
       char nome[50];
       char descricao[100];
       float preco;
       int quantidade;
       char categoria[30];
       int ativo;
};

struct ItemCarrinho
{
       int id_produto;
       char nome_produto[50];
       float preco_unitario;
       int quantidade;
       float subtotal;
};

struct Carrinho
{
       struct ItemCarrinho itens[50];
       int num_itens;
       float valor_total;
       float taxa_entrega;
};

struct Pedido
{
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

struct HorariosSemana
{
       char segunda[13];
       char terca[13];
       char quarta[13];
       char quinta[13];
       char sexta[13];
       char sabado[13];
       char domingo[13];
};

// Protótipos dos Procedimentos
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
void pedidos_cliente_ui();
void pagina_mcdonalds_ui();
void pagina_cocobambu_ui();
void pagina_dominos_ui();
void restaurante_dashboard_ui(struct Cliente *cliente);
void restaurante_pedidos_ui();
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
void exibir_produtos_restaurante_ui(struct Produto produtos[], int num_produtos);
void adicionar_ao_carrinho_ui(struct Carrinho *carrinho, struct Produto produtos[], int num_produtos);
void visualizar_carrinho_ui(struct Carrinho *carrinho);
int menu_carrinho();
void finalizar_compra_ui(struct Carrinho *carrinho, struct Cliente *cliente, struct Pedido pedidos[], int *num_pedidos, struct Produto produtos[], int num_produtos);
void adicionar_favorito_ui(struct Cliente *cliente);
void listar_favoritos_ui(struct Cliente *cliente);
void menu_gerenciar_produtos_ui(struct Produto produtos[], int *num_produtos);

/// Protótipos das Funções
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
void adicionar_item_carrinho(struct Carrinho *carrinho, int id_produto, char nome[], float preco, int quantidade);
void remover_item_carrinho(struct Carrinho *carrinho, int index);
void limpar_carrinho(struct Carrinho *carrinho);
float calcular_total_carrinho(struct Carrinho *carrinho);

int main()
{
       configurarAcentuacao();
       srand(time(NULL)); // Inicializa o gerador de números aleatórios

       struct Cliente cliente;
       struct Produto produtos[100]; // Array para armazenar produtos do restaurante dinâmico
       struct Carrinho carrinho;
       struct Pedido pedidos[100]; // Histórico de pedidos
       int num_produtos = 0;
       int num_pedidos = 0;

       int opcao = 0, tipo = 0, tipo_menu = 0, opcao_home = 0, opcao_restaurante = 0;

       // Inicializa a struct com valores vazios
       memset(&cliente, 0, sizeof(struct Cliente));
       cliente.rest.cadastrado = 0;
       cliente.num_favoritos = 0;

       // Inicializa o carrinho
       inicializar_carrinho(&carrinho);

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
                            cadastro_feito_ui();
                            tipo = enter_ui();
                     }
                     else
                     {
                            cadastro(&cliente);
                            endereco(&cliente.end);
                            le_valida_verificacao(&cliente);
                            tipo = enter_ui();
                     }
                     break;

              case 2:
                     if (strlen(cliente.nome) == 0)
                     {
                            clearScreen();
                            login_nao_cadastrado_ui();
                            tipo = enter_ui();
                     }
                     else
                     {
                            if (cliente.cadastro == 0)
                            {
                                   logar(&cliente);
                            }

                            do
                            {
                                   tipo_menu = 0;
                                   tipo_menu = menu_tipo();

                                   switch (tipo_menu)
                                   {
                                   case 1:
                                          do
                                          {
                                                 modo_cliente_ui(&cliente);
                                                 limparBuffer();

                                                 tipo = 0;
                                                 tipo = menu_cliente();

                                                 switch (tipo)
                                                 {
                                                 case 1:
                                                        do
                                                        {
                                                               home_cliente_ui(); // &cliente
                                                               // favoritos_ui(&cliente);
                                                               opcao_home = menu_home();

                                                               switch (opcao_home)
                                                               {
                                                               case 1:
                                                                      do
                                                                      {
                                                                             pagina_mcdonalds_ui();
                                                                             opcao_restaurante = menu_mcdonalds();
                                                                      } while (opcao_restaurante != 5);
                                                                      break;

                                                               case 2:
                                                                      do
                                                                      {
                                                                             pagina_cocobambu_ui();
                                                                             opcao_restaurante = menu_cocobambu();
                                                                      } while (opcao_restaurante != 5);
                                                                      break;

                                                               case 3:
                                                                      do
                                                                      {
                                                                             pagina_dominos_ui();
                                                                             opcao_restaurante = menu_dominos();
                                                                      } while (opcao_restaurante != 5);
                                                                      break;

                                                               case 4:
                                                                      do
                                                                      {
                                                                             exibir_produtos_restaurante_ui(produtos, num_produtos);

                                                                             printf("\n[1] Adicionar ao Carrinho\n");
                                                                             printf("[2] Ver Carrinho\n\n");
                                                                             printf("[3] Voltar\n\n");

                                                                             int opcao_rest_din;
                                                                             printf("Entre o número desejado: ");
                                                                             if (scanf("%d", &opcao_rest_din) != 1)
                                                                             {
                                                                                    limparBuffer();
                                                                                    opcao_rest_din = 3;
                                                                             }

                                                                             switch (opcao_rest_din)
                                                                             {
                                                                             case 1:
                                                                                    adicionar_ao_carrinho_ui(&carrinho, produtos, num_produtos);
                                                                                    break;
                                                                             case 2:
                                                                                    do
                                                                                    {
                                                                                           visualizar_carrinho_ui(&carrinho);
                                                                                           
                                                                                           // Se carrinho está vazio, sai direto
                                                                                           if (carrinho.num_itens == 0)
                                                                                           {
                                                                                                  enter_ui();
                                                                                                  break;
                                                                                           }
                                                                                           
                                                                                           int opcao_carr = menu_carrinho();

                                                                                           switch (opcao_carr)
                                                                                           {
                                                                                           case 1:
                                                                                                  finalizar_compra_ui(&carrinho, &cliente, pedidos, &num_pedidos, produtos, num_produtos);
                                                                                                  break;
                                                                                           case 2:
                                                                                                  printf("\nDigite o número do item para remover: ");
                                                                                                  int item_remover;
                                                                                                  if (scanf("%d", &item_remover) == 1)
                                                                                                  {
                                                                                                         remover_item_carrinho(&carrinho, item_remover - 1);
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
                                                                             case 3:
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
                                                        pedidos_cliente_ui();
                                                        limparBuffer();
                                                        getchar();
                                                        break;

                                                 case 3:
                                                 {
                                                        int opcao_perfil = 0;
                                                        do
                                                        {
                                                               perfil_cliente_ui(&cliente);

                                                               opcao_perfil = 0;
                                                               opcao_perfil = menu_perfil_cliente();

                                                               switch (opcao_perfil)
                                                               {
                                                               case 1:
                                                               {
                                                                      int opcao_editar = 0;
                                                                      do
                                                                      {
                                                                             editar_perfil_cliente_ui(&cliente);

                                                                             opcao_editar = 0;
                                                                             opcao_editar = menu_editar_perfil_cliente();

                                                                             switch (opcao_editar)
                                                                             {
                                                                             case 1:
                                                                                    int i = 0, ultimo_espaco = 0;
                                                                                    printf("Insira o novo nome: ");
                                                                                    scanf(" %[^\n]s", cliente.nome);
                                                                                    cliente.nome[0] = toupper(cliente.nome[0]);

                                                                                    for (i = 0; i < (int)strlen(cliente.nome); i++)
                                                                                    {
                                                                                           if (cliente.nome[i] == ' ')
                                                                                           {
                                                                                                  ultimo_espaco = i + 1;
                                                                                           }
                                                                                    }

                                                                                    if (ultimo_espaco > 0)
                                                                                    {
                                                                                           cliente.nome[ultimo_espaco] =
                                                                                               toupper(cliente.nome[ultimo_espaco]);
                                                                                    }

                                                                                    printf("O nome foi alterado com sucesso!\n Novo nome: "
                                                                                           "%s\n",
                                                                                           cliente.nome);
                                                                                    enter_ui();
                                                                                    break;

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
                                                                                    if (scanf(" %d", &cliente.end.numero) != 1)
                                                                                    {
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

                                                               case 3:
                                                                      clearScreen();
                                                                      printf("+-----------------------------------------------------------------------+\n");
                                                                      printf("|                         FAVORITOS                                     |\n");
                                                                      printf("+-----------------------------------------------------------------------+\n\n");
                                                                      printf("[1] >> Ver Favoritos\n");
                                                                      printf("[2] >> Adicionar Favorito\n");
                                                                      printf("[3] >> Voltar\n\n");

                                                                      int opcao_fav;
                                                                      printf("Escolha: ");
                                                                      if (scanf("%d", &opcao_fav) == 1)
                                                                      {
                                                                             if (opcao_fav == 1)
                                                                             {
                                                                                    listar_favoritos_ui(&cliente);
                                                                             }
                                                                             else if (opcao_fav == 2)
                                                                             {
                                                                                    adicionar_favorito_ui(&cliente);
                                                                             }
                                                                      }
                                                                      break;

                                                               case 4:
                                                                      excluir_conta_cliente_ui();
                                                                      if (excluir_conta(&cliente) == 1)
                                                                      {
                                                                             opcao_perfil = 5;
                                                                             tipo = 4;      // Sair do menu cliente também
                                                                             tipo_menu = 4; // Sair do menu tipo usuário
                                                                      }
                                                                      printf("\n>> Pressione ENTER para continuar...");
                                                                      limparBuffer();
                                                                      getchar();
                                                                      break;

                                                               case 5:

                                                                      break;

                                                               default:
                                                                      opcao_invalida_ui();
                                                               }
                                                        } while (opcao_perfil != 5);
                                                 }
                                                 break;

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
                                                        enter_ui();
                                                        break;

                                                 case 2:
                                                        restaurante_pedidos_ui();
                                                        enter_ui();
                                                        break;

                                                 case 3:
                                                        restaurante_perfil_ui(&cliente);
                                                        enter_ui();
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
                                                                                    // ** Opereção ternária para alternar o status -
                                                                                    // (condição) ? valor_se_verdadeiro : valor_se_falso **
                                                                                    cliente.rest.status =
                                                                                        (cliente.rest.status == 'a') ? 'f' : 'a';

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

                                                                      tipo = enter_ui();
                                                                      break;

                                                               case 3:
                                                                      horario_funcionamento_ui(&cliente);

                                                                      tipo = 0;
                                                                      tipo = menu_editar_horario_restaurante();

                                                                      switch (tipo)
                                                                      {
                                                                      case 1:
                                                                             editar_horario_semana_ui();
                                                                             printf("Insira o novo horário de abertura (HH:MM): ");
                                                                             scanf(" %5s", cliente.rest.horario_abertura);

                                                                             printf("Insira o novo horário de fechamento (HH:MM): ");
                                                                             scanf(" %5s", cliente.rest.horario_fechamento);

                                                                             printf("\nHorários da semana atualizados com sucesso!\n");
                                                                             printf("Novo horário: %s - %s\n",
                                                                                    cliente.rest.horario_abertura,
                                                                                    cliente.rest.horario_fechamento);
                                                                             tipo = enter_ui();
                                                                             break;

                                                                      case 2:
                                                                             editar_horario_fds_ui();
                                                                             printf("Insira o novo horário de abertura (HH:MM): ");
                                                                             scanf(" %5s", cliente.rest.horario_abertura_fds);

                                                                             printf("Insira o novo horário de fechamento (HH:MM): ");
                                                                             scanf(" %5s", cliente.rest.horario_fechamento_fds);

                                                                             printf("\nHorários do final de semana atualizados com "
                                                                                    "sucesso!\n");
                                                                             printf("Novo horário: %s - %s\n",
                                                                                    cliente.rest.horario_abertura_fds,
                                                                                    cliente.rest.horario_fechamento_fds);
                                                                             tipo = enter_ui();
                                                                             break;

                                                                      case 3:

                                                                             break;
                                                                      }
                                                                      break;

                                                               case 4:
                                                                      menu_gerenciar_produtos_ui(produtos, &num_produtos);
                                                                      break;

                                                               case 5:
                                                                      clearScreen();
                                                                      modo_restaurante_ui(&cliente);
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
                                          // tipo = 0;
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

int menu_editar_horario_restaurante()
{
       int cont = 0;
       int tipo = 0;

       printf("[1] >> Horário da semanda (Seg-Sex)\n");
       printf("[2] >> Horário do final de semana (Sáb-Dom)\n\n");

       printf("[3] >> Voltar\n");

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
       } while (tipo != 1 && tipo != 2 && tipo != 3);

       return tipo;
}

int menu_perfil_cliente()
{
       int cont = 0;
       int tipo = 0;

       printf("[1] >> Editar Perfil\n");
       printf("[2] >> Alterar Senha\n");
       printf("[3] >> Favoritos\n");
       printf("[4] >> Excluir Conta\n\n");
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

int menu_home()
{
       int cont = 0;
       int tipo = 0;

       printf(" +-----------------------------------------------------------------------+\n");
       printf(" |  [1]  McDonald's                                       * 4.5          |\n");
       printf(" |       Lanches  -  30-40 min  -  R$ 5.99                               |\n");
       printf(" +-----------------------------------------------------------------------+\n\n");

       printf(" +-----------------------------------------------------------------------+\n");
       printf(" |  [2]  Coco Bambu                                       * 4.8          |\n");
       printf(" |       Frutos do Mar  -  50-60 min  -  R$ 12.00                        |\n");
       printf(" +-----------------------------------------------------------------------+\n\n");

       printf(" +-----------------------------------------------------------------------+\n");
       printf(" |  [3]  Domino's Pizza                                   * 4.2          |\n");
       printf(" |       Pizza  -  40-50 min  -  Gratis                                  |\n");
       printf(" +-----------------------------------------------------------------------+\n\n");

       printf(" +-----------------------------------------------------------------------+\n");
       printf(" |  [4]  Restaurante Dinamico                             * 5.0          |\n");
       printf(" |       Variado  -  20-30 min  -  R$ 8.00                               |\n");
       printf(" +-----------------------------------------------------------------------+\n\n");

       printf("[5] >> Voltar\n\n");

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

int menu_mcdonalds()
{
       int cont = 0;
       int tipo = 0;

       printf("   Hamburgueres\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [1]  Big Mac                                         +-------+       |\n");
       printf("   |       Dois hamburgueres, alface, queijo especial      |       |       |\n");
       printf("   |       R$ 28.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [2]  Quarteirão com Queijo                           +-------+       |\n");
       printf("   |       Hamburguer, queijo, picles, cebola e ketchup    |       |       |\n");
       printf("   |       R$ 26.50                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   Acompanhamentos\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [3]  Batata Frita Media                              +-------+       |\n");
       printf("   |       Batatas crocantes e sequinhas                   |       |       |\n");
       printf("   |       R$ 12.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   Bebidas\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [4]  Coca-Cola 500ml                                 +-------+       |\n");
       printf("   |       Refrigerante gelado                             |       |       |\n");
       printf("   |       R$ 7.50                                         | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   [5] >> Voltar\n\n");

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

int menu_cocobambu()
{
       int cont = 0;
       int tipo = 0;

       printf("   Pratos Principais\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [1]  Camarão Internacional                           +-------+       |\n");
       printf("   |       Camarões ao molho de coco com arroz             |       |       |\n");
       printf("   |       R$ 89.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [2]  Lagosta Grelhada                                +-------+       |\n");
       printf("   |       Lagosta inteira grelhada com manteiga           |       |       |\n");
       printf("   |       R$ 149.90                                       | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   Acompanhamentos\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [3]  Arroz de Coco                                   +-------+       |\n");
       printf("   |       Arroz especial preparado com leite de coco      |       |       |\n");
       printf("   |       R$ 18.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   Bebidas\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [4]  Caipirinha de Limão                             +-------+       |\n");
       printf("   |       Bebida refrescante com limão                    |       |       |\n");
       printf("   |       R$ 22.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   [5] >> Voltar\n\n");

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

int menu_dominos()
{
       int cont = 0;
       int tipo = 0;

       printf("   Pizzas\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [1]  Pizza Pepperoni Grande                          +-------+       |\n");
       printf("   |       Mussarela, pepperoni e oregano                  |       |       |\n");
       printf("   |       R$ 54.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [2]  Pizza Margherita Grande                         +-------+       |\n");
       printf("   |       Mussarela, tomate, manjericão e oregano         |       |       |\n");
       printf("   |       R$ 49.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   Acompanhamentos\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [3]  Palitos de Queijo                               +-------+       |\n");
       printf("   |       Palitos crocantes recheados com queijo          |       |       |\n");
       printf("   |       R$ 19.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   Bebidas\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  [4]  Refrigerante 2L                                 +-------+       |\n");
       printf("   |       Coca-Cola, Guarana ou Fanta                     |       |       |\n");
       printf("   |       R$ 12.90                                        | [IMG] |       |\n");
       printf("   |                                                       |       |       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       printf("   [5] >> Voltar\n\n");

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

// Função do Menu configurações do restaurante
int menu_configuracoes_restaurante(struct Cliente *cliente)
{
       (void)cliente; // Parâmetro não utilizado no momento
       int cont = 0;
       int tipo = 0;

       printf("[1] >> Dados do Restaurante\n");
       printf("[2] >> Status do Restaurante\n");
       printf("[3] >> Horários de Funcionamento\n");
       printf("[4] >> Gerenciar Produtos\n\n");

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
       int primeiro_espaco = 0, i = 0, cont = 0;

       cadastro_restaurante_ui();

       printf("Digite o nome do restaurante: ");
       scanf(" %[^\n]s", nome);
       nome[0] = toupper(nome[0]);

       printf("Digite o tipo de culinária: ");
       scanf(" %[^\n]s", tipo);
       tipo[0] = toupper(tipo[0]);

       printf("Digite o telefone do restaurante: ");
       scanf(" %s", telefone);

       printf("Digite o endereço do restaurante: ");
       scanf(" %19[^\n]", cliente->rest.end.endereco);

       for (i = 0; i < (int)strlen(cliente->rest.end.endereco); i++)
       {
              if (cliente->rest.end.endereco[i] == ' ' && cont == 0)
              {
                     primeiro_espaco = i;
                     cont++;
              }
       }

       for (i = 0; i < primeiro_espaco; i++)
       {
              cliente->rest.end.endereco[i] = toupper(cliente->rest.end.endereco[i]);
       }

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
       enter_ui();
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

       for (i = 0; i < (int)strlen(nome); i++)
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
       enter_ui();
       return 0;
}

// funçaõ cadastro entregador ------------
int cadastro_entregador(struct Entregador *entregador,
                        struct Cliente *cliente)
{
       (void)entregador; // Parâmetro não utilizado no momento
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

              if (strcmp(email, cliente->email) != 0 ||
                  strcmp(senha, cliente->senha) != 0)
              {
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
       enter_ui();
       return 0;
}

char *alterar_senha(struct Cliente *cliente)
{
       int cont = 0;
       char senha[20];
       strcpy(senha, cliente->senha);

       do
       {
              if (cont > 0)
              {
                     printf("Senha incorreta! Tente novamente: ");
                     scanf(" %s", senha);
              }
              else
              {
                     printf("Insira a Senha atual para confirmação: ");
                     scanf(" %s", senha);
              }
              cont++;
       } while (strcmp(senha, cliente->senha) != 0);

       cont = 0;
       do
       {
              if (cont > 0)
              {
                     printf("Senha igual a anterior! Tente novamente: ");
                     scanf(" %s", cliente->senha);
              }
              else
              {
                     printf("\nInsira Senha nova: ");
                     scanf(" %s", cliente->senha);
              }
              cont++;
       } while (strcmp(senha, cliente->senha) == 0);

       return cliente->senha;
}

int excluir_conta(struct Cliente *cliente)
{
       char delete_confirm;
       int cont = 0;
       char senha[20];

       printf("Tem certeza que deseja excluir sua "
              "conta? Essa ação é irreversível. (s/n): ");
       scanf(" %c", &delete_confirm);

       if (delete_confirm == 's' || delete_confirm == 'S')
       {
              do
              {
                     if (cont > 0)
                     {
                            printf("Senha incorreta! Tente novamente: ");
                            scanf(" %19s", senha);
                     }
                     else
                     {
                            printf("\nInsira a Senha atual para confirmação: ");
                            scanf(" %19s", senha);
                     }
                     cont++;
              } while (strcmp(senha, cliente->senha) != 0);

              cliente->cadastro = 0;
              memset(cliente, 0, sizeof(struct Cliente));
              printf("\nConta excluída com sucesso!\n");
              return 1;
       }
       else
       {
              printf("\nOperação cancelada. Sua conta não foi excluída.\n");
       }
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

// Procedimento paar pausar a interface do usuário
int enter_ui()
{
       printf("\n>> Pressione ENTER para continuar...");
       limparBuffer();
       getchar();
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
       printf("||        Bem-vindo à sua experiência de delivery direto no "
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

void login_ui()
{
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

void login_error_ui()
{
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

void cadastro_ui()
{
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

void cadastro_feito_ui()
{
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
       printf("                 Usuário já cadastrado! Tente logar.                 "
              "      \n\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void code_ui(struct Cliente *cliente)
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|                 V E R I F I C A Ç Ã O   D E   C Ó D I G O          "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("     Para finalizar seu cadastro, enviamos um código de verificação "
              "para:  \n\n");
       printf("     E-mail: %s                                                      "
              "       \n\n",
              cliente->email);
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void endereco_ui()
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|                I N F O R M A Ç Õ E S   D E   E N T R E G A         "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("     Para finalizar, precisamos do seu endereço para entrega dos "
              "pedidos   \n\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void modo_select_entrada_ui()
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|                     S E L E Ç Ã O  D E  E N T R A D A              "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("                         O que você deseja fazer?                    "
              "      \n\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void modo_cliente_ui(struct Cliente *cliente)
{

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
       printf("                         O que você deseja fazer?\n");
       printf("                Endereço: %s, %s, %d, CEP: %s  \n",
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
       printf("                      O que você está procurando?                    "
              "      \n\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n");
}

void pagina_mcdonalds_ui()
{
       clearScreen();
       printf("\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |                                                                       |\n");
       printf("   |                          McDonald's                                   |\n");
       printf("   |                                                                       |\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  McDonald's                                                           |\n");
       printf("   |  * 4.5 - 30-40 min - R$ 5.99                                          |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");
}

void pagina_cocobambu_ui()
{
       clearScreen();
       printf("\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |                                                                       |\n");
       printf("   |                    '      Coco Bambu                                   |\n");
       printf("   |                                                                       |\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  Coco Bambu                                                           |\n");
       printf("   |  * 4.8 - 50-60 min - R$ 12.00                                         |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");
}

void pagina_dominos_ui()
{
       clearScreen();
       printf("\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |                                                                       |\n");
       printf("   |                        Domino's Pizza                                 |\n");
       printf("   |                                                                       |\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  Domino's Pizza                                                       |\n");
       printf("   |  * 4.2 - 40-50 min - Gratis                                           |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");
}

void modo_entregador_ui(struct Cliente *cliente)
{
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
       printf("                         O que você deseja fazer?                    "
              "      \n\n");
       printf("                  Endereço: %s, %s, %d, CEP: %s                      "
              "      \n",
              cliente->end.endereco, cliente->end.logradouro, cliente->end.numero,
              cliente->end.cep);
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void modo_restaurante_ui(struct Cliente *cliente)
{
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
       printf("                         O que você deseja fazer?                    "
              "      \n\n");
       printf("                 Endereço: %s, %s, %d, CEP: %s                       "
              "      \n",
              cliente->rest.end.endereco, cliente->rest.end.logradouro,
              cliente->rest.end.numero, cliente->end.cep);
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void pedidos_cliente_ui()
{
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
       printf("                         Seus pedidos recentes:                      "
              "      \n\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void perfil_cliente_ui(struct Cliente *cliente)
{
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
       printf("Endrereço de Entrega: %s, %s, %d, CEP: %s                            "
              "      \n\n",
              cliente->end.endereco, cliente->end.logradouro, cliente->end.numero,
              cliente->end.cep);
}

void editar_perfil_cliente_ui(struct Cliente *cliente)
{
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

void alterar_senha_cliente_ui(struct Cliente *cliente)
{
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

void excluir_conta_cliente_ui()
{
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
       printf("    Tem certeza que deseja excluir sua conta? Esta ação é "
              "irreversível     \n\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void restaurante_dashboard_ui(struct Cliente *cliente)
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|                   R E S T A U R A N T E   D A S H B O A R D        "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("                       Visão geral do restaurante: %s                "
              "      \n\n",
              cliente->rest.status == 'a' ? "Aberto" : "Fechado");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void restaurante_pedidos_ui()
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|                   R E S T A U R A N T E   P E D I D O S            "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("                         Pedidos recebidos:                          "
              "      \n\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void restaurante_perfil_ui(struct Cliente *cliente)
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|                 R E S T A U R A N T E   P E R F I L                "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("                 Nome do Restaurante:%s | Email:%s                   "
              "      \n\n",
              cliente->nome, cliente->email);
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void restaurante_configuracoes_ui()
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|               R E S T A U R A N T E   C O N F I G U R A Ç Õ E S    "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("                     Ajuste as configurações do restaurante:         "
              "      \n\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void status_restaurante_ui(struct Cliente *cliente)
{
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

void dados_restaurante_ui()
{
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
       printf("                       Informações do restaurante:                   "
              "      \n");
}

void horario_funcionamento_ui(struct Cliente *cliente)
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|             H O R Á R I O   D E   F U N C I O N A M E N T O        "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
       printf("                       Segunda - Sexta: %s - %s               \n",
              cliente->rest.horario_abertura, cliente->rest.horario_fechamento);
       printf("                       Sábado - Domingo: %s - %s               \n\n",
              cliente->rest.horario_abertura_fds,
              cliente->rest.horario_fechamento_fds);
       printf("  "
              "+--------------------------------------------------------------------"
              "-+  \n\n");
}

void cadastro_restaurante_ui()
{
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

void dados_gerais_restaurante_ui(struct Cliente *cliente)
{
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
       printf("  | ENDEREÇO                                                         "
              "   |\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+\n");
       printf("  | Endereço:   %-54s  |\n", cliente->rest.end.endereco);
       printf("  | Logradouro: %-54s  |\n", cliente->rest.end.logradouro);
       printf("  | Número:     %-54d  |\n", cliente->rest.end.numero);
       printf("  | CEP:        %-54s  |\n", cliente->rest.end.cep);
       printf("  "
              "+--------------------------------------------------------------------"
              "-+\n\n");

       printf("  "
              "+--------------------------------------------------------------------"
              "-+\n");
       printf("  | HORÁRIOS DE FUNCIONAMENTO                                        "
              "   |\n");
       printf("  "
              "+--------------------------------------------------------------------"
              "-+\n");
       printf("  | Segunda - Sexta: %s - %-42s |\n", cliente->rest.horario_abertura,
              cliente->rest.horario_fechamento);
       printf("  | Sábado - Domingo: %s - %-41s |\n",
              cliente->rest.horario_abertura_fds,
              cliente->rest.horario_fechamento_fds);
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
       if (cliente->rest.status == 'a')
       {
              printf("  | >>>>>   A B E R T O   <<<<<                                    "
                     "     |\n");
       }
       else
       {
              printf("  | >>>>>   F E C H A D O   <<<<<                                  "
                     "     |\n");
       }
       printf("  "
              "+--------------------------------------------------------------------"
              "-+\n\n");

       enter_ui();
}

void login_nao_cadastrado_ui()
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "----------+\n");
       printf("|                                                                    "
              "          |\n");
       printf("|                           USUÁRIO NÃO CADASTRADO                   "
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

void opcao_invalida_ui()
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "----------+\n");
       printf("|                                                                    "
              "          |\n");
       printf("|           O P Ç Ã O  I N V Á L I D A !  T E N T E  N O V A M E N T "
              "E         |\n");
       printf("|                                                                    "
              "          |\n");
       printf("+--------------------------------------------------------------------"
              "----------+\n");
       enter_ui();
}

void editar_horario_semana_ui()
{
       clearScreen();
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|             E D I T A R   H O R Á R I O   D A   S E M A N A        "
              "     |\n");
       printf("|                        ( S e g u n d a   -   S e x t a )           "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
}

void editar_horario_fds_ui()
{
       printf("+--------------------------------------------------------------------"
              "-----+\n");
       printf("|                                                                    "
              "     |\n");
       printf("|    E D I T A R   H O R Á R I O   D O   F I N A L   D E   S E M A N "
              "A    |\n");
       printf("|                    ( S á b a d o   -   D o m i n g o )             "
              "     |\n");
       printf("|                                                                    "
              "     |\n");
       printf("+--------------------------------------------------------------------"
              "-----+\n\n");
}

void restaurante_dinamico_ui()
{
       clearScreen();
       printf("\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |                                                                       |\n");
       printf("   |                        RESTAURANTE DINÂMICO                           |\n");
       printf("   |                                                                       |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");
       printf("\n");
       printf("                        EM DESENVOLVIMENTO                                \n\n");
       printf("              Faz parte do modulo extra do projeto                        \n\n");
       printf("   +-----------------------------------------------------------------------+\n\n");
}

// ==================== FUNÇÕES DO CARRINHO ====================

void inicializar_carrinho(struct Carrinho *carrinho)
{
       carrinho->num_itens = 0;
       carrinho->valor_total = 0.0;
       carrinho->taxa_entrega = 0.0;
}

void adicionar_item_carrinho(struct Carrinho *carrinho, int id_produto, char nome[], float preco, int quantidade)
{
       if (carrinho->num_itens >= 50)
       {
              printf("Carrinho cheio! Não é possível adicionar mais itens.\n");
              return;
       }

       // Verifica se o produto já está no carrinho
       for (int i = 0; i < carrinho->num_itens; i++)
       {
              if (carrinho->itens[i].id_produto == id_produto)
              {
                     carrinho->itens[i].quantidade += quantidade;
                     carrinho->itens[i].subtotal = carrinho->itens[i].quantidade * carrinho->itens[i].preco_unitario;
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

void remover_item_carrinho(struct Carrinho *carrinho, int index)
{
       if (index < 0 || index >= carrinho->num_itens)
       {
              printf("Item inválido!\n");
              return;
       }

       // Desloca os itens
       for (int i = index; i < carrinho->num_itens - 1; i++)
       {
              carrinho->itens[i] = carrinho->itens[i + 1];
       }

       carrinho->num_itens--;
       printf("\n✓ Item removido do carrinho!\n");
}

void limpar_carrinho(struct Carrinho *carrinho)
{
       carrinho->num_itens = 0;
       carrinho->valor_total = 0.0;
       carrinho->taxa_entrega = 0.0;
}

float calcular_total_carrinho(struct Carrinho *carrinho)
{
       float total = 0.0;
       for (int i = 0; i < carrinho->num_itens; i++)
       {
              total += carrinho->itens[i].subtotal;
       }
       carrinho->valor_total = total + carrinho->taxa_entrega;
       return carrinho->valor_total;
}

// ==================== FUNÇÕES DE PRODUTOS ====================

void cadastrar_produto_ui(struct Produto produtos[], int *num_produtos)
{
       if (*num_produtos >= 100)
       {
              printf("\nLimite de produtos atingido!\n");
              enter_ui();
              return;
       }

       clearScreen();
       printf("+-----------------------------------------------------------------------+\n");
       printf("|                        CADASTRAR NOVO PRODUTO                         |\n");
       printf("+-----------------------------------------------------------------------+\n\n");

       struct Produto novo;
       novo.id = *num_produtos + 1;

       printf("Nome do produto: ");
       scanf(" %49[^\n]", novo.nome);

       printf("Descrição: ");
       scanf(" %99[^\n]", novo.descricao);

       printf("Preço (R$): ");
       if (scanf("%f", &novo.preco) != 1)
       {
              limparBuffer();
              novo.preco = 0.0;
       }

       printf("Quantidade em estoque: ");
       if (scanf("%d", &novo.quantidade) != 1)
       {
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

void listar_produtos_ui(struct Produto produtos[], int num_produtos)
{
       clearScreen();
       printf("+-----------------------------------------------------------------------+\n");
       printf("|                        PRODUTOS CADASTRADOS                           |\n");
       printf("+-----------------------------------------------------------------------+\n\n");

       if (num_produtos == 0)
       {
              printf("Nenhum produto cadastrado ainda.\n\n");
              enter_ui();
              return;
       }

       for (int i = 0; i < num_produtos; i++)
       {
              printf("ID: %d | %s %s\n", produtos[i].id, produtos[i].ativo ? "[✓]" : "[X]", produtos[i].nome);
              printf("   Categoria: %s | Preço: R$ %.2f | Estoque: %d\n", produtos[i].categoria, produtos[i].preco, produtos[i].quantidade);
              printf("   Descrição: %s\n", produtos[i].descricao);
              printf("-----------------------------------------------------------------------\n");
       }

       enter_ui();
}

int menu_gerenciar_produtos()
{
       int opcao;
       int cont = 0;

       printf("\n[1] >> Cadastrar Produto\n");
       printf("[2] >> Listar Produtos\n");
       printf("[3] >> Editar Produto\n");
       printf("[4] >> Ativar/Desativar Produto\n\n");
       printf("[5] >> Voltar\n\n");

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
       } while (opcao < 1 || opcao > 5);

       return opcao;
}

void menu_gerenciar_produtos_ui(struct Produto produtos[], int *num_produtos)
{
       int opcao;

       do
       {
              clearScreen();
              printf("+-----------------------------------------------------------------------+\n");
              printf("|                         GERENCIAR PRODUTOS                            |\n");
              printf("+-----------------------------------------------------------------------+\n");

              opcao = menu_gerenciar_produtos();

              switch (opcao)
              {
              case 1:
                     cadastrar_produto_ui(produtos, num_produtos);
                     break;

              case 2:
                     listar_produtos_ui(produtos, *num_produtos);
                     break;

              case 3:
                     printf("\nFuncionalidade em desenvolvimento...\n");
                     enter_ui();
                     break;

              case 4:
                     printf("\nFuncionalidade em desenvolvimento...\n");
                     enter_ui();
                     break;

              case 5:
                     break;
              }

       } while (opcao != 5);
}

// ==================== FUNÇÕES DE EXIBIÇÃO E COMPRA ====================

void exibir_produtos_restaurante_ui(struct Produto produtos[], int num_produtos)
{
       clearScreen();
       printf("\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |                         RESTAURANTE DINÂMICO                          |\n");
       printf("   +-----------------------------------------------------------------------+\n");
       printf("   |  * 5.0 - 20-30 min - R$ 8.00                                          |\n");
       printf("   +-----------------------------------------------------------------------+\n\n");

       if (num_produtos == 0)
       {
              printf("   Nenhum produto cadastrado ainda.\n\n");
              return;
       }

       char categorias[10][30];
       int num_categorias = 0;

       for (int i = 0; i < num_produtos; i++)
       {
              if (!produtos[i].ativo)
                     continue;

              int encontrou = 0;
              for (int j = 0; j < num_categorias; j++)
              {
                     if (strcmp(categorias[j], produtos[i].categoria) == 0)
                     {
                            encontrou = 1;
                            break;
                     }
              }

              if (!encontrou)
              {
                     strcpy(categorias[num_categorias], produtos[i].categoria);
                     num_categorias++;
              }
       }

       for (int cat = 0; cat < num_categorias; cat++)
       {
              printf("   %s\n", categorias[cat]);

              for (int i = 0; i < num_produtos; i++)
              {
                     if (produtos[i].ativo && strcmp(produtos[i].categoria, categorias[cat]) == 0)
                     {
                            printf("   +-----------------------------------------------------------------------+\n");
                            printf("   |  [%d]  %-58s       |\n", produtos[i].id, produtos[i].nome);
                            printf("   |       %-58s     |\n", produtos[i].descricao);
                            printf("   |       R$ %.2f  -  Estoque: %d                                         |\n", produtos[i].preco, produtos[i].quantidade);
                            printf("   +-----------------------------------------------------------------------+\n\n");
                     }
              }
       }
}

void adicionar_ao_carrinho_ui(struct Carrinho *carrinho, struct Produto produtos[], int num_produtos)
{
       clearScreen();
       
       if (num_produtos == 0)
       {
              printf("\nNenhum produto disponível para adicionar.\n");
              enter_ui();
              return;
       }

       printf("+-----------------------------------------------------------------------+\n");
       printf("|                    ADICIONAR AO CARRINHO                              |\n");
       printf("+-----------------------------------------------------------------------+\n\n");

       int id_produto, quantidade;

       printf("\nDigite o ID do produto: ");
       if (scanf("%d", &id_produto) != 1)
       {
              limparBuffer();
              printf("ID inválido!\n");
              enter_ui();
              return;
       }

       // Busca o produto
       int encontrado = -1;
       for (int i = 0; i < num_produtos; i++)
       {
              if (produtos[i].id == id_produto && produtos[i].ativo)
              {
                     encontrado = i;
                     break;
              }
       }

       if (encontrado == -1)
       {
              printf("\nProduto não encontrado ou indisponível!\n");
              enter_ui();
              return;
       }

       printf("Digite a quantidade: ");
       if (scanf("%d", &quantidade) != 1 || quantidade <= 0)
       {
              limparBuffer();
              printf("Quantidade inválida!\n");
              enter_ui();
              return;
       }

       if (quantidade > produtos[encontrado].quantidade)
       {
              printf("\nEstoque insuficiente! Disponível: %d\n", produtos[encontrado].quantidade);
              enter_ui();
              return;
       }

       adicionar_item_carrinho(carrinho, produtos[encontrado].id, produtos[encontrado].nome, produtos[encontrado].preco, quantidade);
       enter_ui();
}

void visualizar_carrinho_ui(struct Carrinho *carrinho)
{
       clearScreen();
       printf("+-----------------------------------------------------------------------+\n");
       printf("|                         MEU CARRINHO                                  |\n");
       printf("+-----------------------------------------------------------------------+\n\n");

       if (carrinho->num_itens == 0)
       {
              printf("Carrinho vazio.\n\n");
              return;
       }

       for (int i = 0; i < carrinho->num_itens; i++)
       {
              printf("[%d] %s\n", i + 1, carrinho->itens[i].nome_produto);
              printf("    R$ %.2f x %d = R$ %.2f\n", carrinho->itens[i].preco_unitario, carrinho->itens[i].quantidade, carrinho->itens[i].subtotal);
              printf("-----------------------------------------------------------------------\n");
       }

       float total = calcular_total_carrinho(carrinho);
       printf("\nSubtotal: R$ %.2f\n", total - carrinho->taxa_entrega);
       printf("Taxa de Entrega: R$ %.2f\n", carrinho->taxa_entrega);
       printf("TOTAL: R$ %.2f\n\n", total);
}

int menu_carrinho()
{
       int opcao;
       int cont = 0;

       printf("[1] >> Finalizar Compra\n");
       printf("[2] >> Remover Item\n");
       printf("[3] >> Limpar Carrinho\n\n");
       printf("[4] >> Voltar\n\n");

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
       } while (opcao < 1 || opcao > 4);

       return opcao;
}

void finalizar_compra_ui(struct Carrinho *carrinho, struct Cliente *cliente, struct Pedido pedidos[], int *num_pedidos, struct Produto produtos[], int num_produtos)
{
       (void)num_produtos; // Parâmetro usado indiretamente no loop de atualização de estoque
       
       if (carrinho->num_itens == 0)
       {
              printf("\nCarrinho vazio! Adicione produtos antes de finalizar.\n");
              enter_ui();
              return;
       }

       clearScreen();
       printf("+-----------------------------------------------------------------------+\n");
       printf("|                      FINALIZAR COMPRA                                 |\n");
       printf("+-----------------------------------------------------------------------+\n\n");

       // Mostra resumo
       visualizar_carrinho_ui(carrinho);

       // Confirmação de endereço
       printf("\nEndereço de entrega:\n");
       printf("%s, %s, %d - CEP: %s\n\n", cliente->end.endereco, cliente->end.logradouro, cliente->end.numero, cliente->end.cep);

       // Forma de pagamento
       char forma_pagamento[20];
       printf("Forma de pagamento:\n");
       printf("[1] Dinheiro\n");
       printf("[2] Cartão de Crédito\n");
       printf("[3] Cartão de Débito\n");
       printf("[4] PIX\n\n");

       int opcao_pag;
       printf("Escolha: ");
       if (scanf("%d", &opcao_pag) != 1)
       {
              limparBuffer();
              printf("Opção inválida!\n");
              enter_ui();
              return;
       }

       switch (opcao_pag)
       {
       case 1:
              strcpy(forma_pagamento, "Dinheiro");
              break;
       case 2:
              strcpy(forma_pagamento, "Cartão Crédito");
              break;
       case 3:
              strcpy(forma_pagamento, "Cartão Débito");
              break;
       case 4:
              strcpy(forma_pagamento, "PIX");
              break;
       default:
              strcpy(forma_pagamento, "Não informado");
       }

       // Confirmação final
       char confirmar;
       printf("\nConfirmar pedido? (s/n): ");
       scanf(" %c", &confirmar);

       if (confirmar == 's' || confirmar == 'S')
       {
              // Cria o pedido
              struct Pedido novo_pedido;
              novo_pedido.id = *num_pedidos + 1;
              strcpy(novo_pedido.cpf_cliente, cliente->cpf);
              strcpy(novo_pedido.nome_restaurante, "Restaurante Dinâmico");

              for (int i = 0; i < carrinho->num_itens; i++)
              {
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
              printf("Número do pedido: #%d\n", novo_pedido.id);
              printf("Status: %s\n\n", novo_pedido.status);

              // Atualiza o estoque dos produtos
              for (int i = 0; i < carrinho->num_itens; i++)
              {
                     int id_produto = carrinho->itens[i].id_produto;
                     int qtd_comprada = carrinho->itens[i].quantidade;
                     
                     // Busca o produto e atualiza o estoque
                     for (int j = 0; j < 100; j++) // num_produtos máximo
                     {
                            if (produtos[j].id == id_produto)
                            {
                                   produtos[j].quantidade -= qtd_comprada;
                                   break;
                            }
                     }
              }

              limpar_carrinho(carrinho);
       }
       else
       {
              printf("\nPedido cancelado.\n");
       }

       enter_ui();
}

// ==================== FUNÇÕES DE FAVORITOS ====================

void adicionar_favorito_ui(struct Cliente *cliente)
{
       if (cliente->num_favoritos >= 10)
       {
              printf("\nLimite de favoritos atingido!\n");
              enter_ui();
              return;
       }

       printf("\nAdicionar restaurante aos favoritos:\n");
       printf("[1] McDonald's\n");
       printf("[2] Coco Bambu\n");
       printf("[3] Domino's Pizza\n");
       printf("[4] Restaurante Dinâmico\n\n");

       int opcao;
       printf("Escolha: ");
       if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4)
       {
              limparBuffer();
              printf("Opção inválida!\n");
              enter_ui();
              return;
       }

       // Verifica se já está nos favoritos
       for (int i = 0; i < cliente->num_favoritos; i++)
       {
              if (cliente->restaurantes_favoritos[i] == opcao)
              {
                     printf("\nRestaurante já está nos favoritos!\n");
                     enter_ui();
                     return;
              }
       }

       cliente->restaurantes_favoritos[cliente->num_favoritos] = opcao;
       cliente->num_favoritos++;

       printf("\n✓ Restaurante adicionado aos favoritos!\n");
       enter_ui();
}

void listar_favoritos_ui(struct Cliente *cliente)
{
       clearScreen();
       printf("+-----------------------------------------------------------------------+\n");
       printf("|                    RESTAURANTES FAVORITOS                             |\n");
       printf("+-----------------------------------------------------------------------+\n\n");

       if (cliente->num_favoritos == 0)
       {
              printf("Nenhum restaurante favorito ainda.\n\n");
              enter_ui();
              return;
       }

       char *nomes[] = {"", "McDonald's", "Coco Bambu", "Domino's Pizza", "Restaurante Dinâmico"};

       for (int i = 0; i < cliente->num_favoritos; i++)
       {
              int id = cliente->restaurantes_favoritos[i];
              printf("[%d] %s\n", i + 1, nomes[id]);
       }

       printf("\n");
       enter_ui();
}