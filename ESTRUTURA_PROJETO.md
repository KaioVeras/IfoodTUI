# 📐 Estrutura do Projeto IfoodTUI

## 📋 Índice
- [Visão Geral](#-visão-geral)
- [Estrutura de Arquivos](#-estrutura-de-arquivos)
- [Arquitetura do Código](#-arquitetura-do-código)
- [Estruturas de Dados](#-estruturas-de-dados)
- [Fluxo de Execução](#-fluxo-de-execução)
- [Organização do Desenvolvimento](#-organização-do-desenvolvimento)
- [Padrões e Convenções](#-padrões-e-convenções)

---

## 🎯 Visão Geral

O **IfoodTUI** é um sistema monolítico desenvolvido em C puro, com aproximadamente **4.600 linhas de código**, implementando um sistema completo de delivery com interface de texto (TUI). O projeto utiliza programação estruturada e manipulação de arquivos para persistência de dados.

### Características Técnicas
- **Linguagem**: C (padrão ANSI C)
- **Paradigma**: Programação Estruturada
- **Tamanho**: ~4.600 linhas de código
- **Arquitetura**: Monolítica com separação lógica de módulos
- **Persistência**: Arquivos binários/texto

---

## 📂 Estrutura de Arquivos

```
IfoodTUI/
│
├── main.c                          # Arquivo principal (~4.600 linhas)
│   ├── Includes                    # Bibliotecas padrão C
│   ├── Definição de Structs        # Estruturas de dados
│   ├── Protótipos de Funções       # Declarações antecipadas
│   ├── Função main()               # Ponto de entrada
│   ├── Funções de Lógica           # Regras de negócio
│   └── Funções de UI               # Interface do usuário
│
├── main                            # Executável compilado (Linux/Mac)
├── output/                         # Diretório de saída
│
├── README.md                       # Documentação principal
├── ESTRUTURA_PROJETO.md           # Este arquivo
│
└── .git/                          # Controle de versão Git
```

---

## 🏗️ Arquitetura do Código

O código está organizado em **camadas lógicas** dentro do arquivo `main.c`:

### 1️⃣ Camada de Bibliotecas (Linhas 1-13)
```c
#include <ctype.h>      // Manipulação de caracteres
#include <locale.h>     // Suporte a acentuação
#include <stdio.h>      // Entrada/saída padrão
#include <stdlib.h>     // Funções de utilidade
#include <string.h>     // Manipulação de strings
#include <time.h>       // Data e hora
```

### 2️⃣ Camada de Estruturas de Dados (Linhas 15-113)
Definição de todas as `structs` utilizadas no sistema:
- `Endereco`: Armazena dados de localização
- `Entregador`: Informações do entregador
- `HorarioDia`: Horários de funcionamento
- `Restaurante`: Dados completos do estabelecimento
- `Cliente`: Perfil do usuário cliente
- `Produto`: Itens do cardápio
- `ItemCarrinho`: Produtos no carrinho
- `Carrinho`: Carrinho de compras completo
- `Pedido`: Pedido realizado com histórico

### 3️⃣ Camada de Protótipos (Linhas 116-200)
Declaração antecipada de todas as funções do sistema, divididas em:
- **Funções de UI** (`*_ui()`): Exibição de interfaces
- **Funções de Menu** (`menu_*()`): Navegação e opções
- **Funções de Lógica**: Processamento de dados

### 4️⃣ Função Principal `main()` (Linhas ~220-600)
Inicialização do sistema e loop principal:
```c
int main() {
    // 1. Configuração inicial
    configurarAcentuacao();
    srand(time(NULL));
    
    // 2. Declaração de variáveis
    struct Cliente cliente;
    struct Produto produtos[100];
    struct Carrinho carrinho;
    struct Pedido pedidos[100];
    
    // 3. Inicialização de dados
    inicializar_carrinho(&carrinho);
    inicializar_produtos_*();
    
    // 4. Loop principal do menu
    do {
        // Lógica de navegação
    } while (opcao != 0);
}
```

### 5️⃣ Camada de Lógica de Negócio (Linhas ~600-2400)
Implementação das regras de negócio:
- **Autenticação**: `cadastro()`, `logar()`
- **Carrinho**: `adicionar_item_carrinho()`, `remover_item_carrinho()`
- **Pedidos**: `finalizar_compra_ui()`, `gerenciar_status_pedido()`
- **Produtos**: `cadastrar_produto_ui()`, `listar_produtos_ui()`
- **Favoritos**: `adicionar_favorito_ui()`, `listar_favoritos_ui()`

### 6️⃣ Camada de Interface (Linhas ~2400-4600)
Funções de UI para exibição no terminal:
- **Menus**: `menu_ui()`, `home_cliente_ui()`, `restaurante_dashboard_ui()`
- **Formulários**: `cadastro_ui()`, `login_ui()`, `endereco_ui()`
- **Feedback**: `opcao_invalida_ui()`, `cadastro_feito_ui()`
- **Utilidades**: `clearScreen()`, `limparBuffer()`

---

## 🗃️ Estruturas de Dados

### Estrutura `Cliente`
```c
struct Cliente {
    struct Endereco end;                // Endereço de entrega
    struct Restaurante rest;            // Dados do restaurante (se for dono)
    char nome[30];                      // Nome completo
    char cpf[11];                       // CPF (apenas dígitos)
    char email[20];                     // Email
    char telefone[20];                  // Telefone
    char senha[20];                     // Senha
    int cadastro;                       // Flag de cadastro completo
    int restaurantes_favoritos[10];     // IDs dos favoritos
    int num_favoritos;                  // Quantidade de favoritos
    int produtos_favoritos[50];         // IDs dos produtos favoritos
    int num_produtos_favoritos;         // Quantidade de produtos favoritos
};
```

### Estrutura `Produto`
```c
struct Produto {
    int id;                             // Identificador único
    char nome[50];                      // Nome do produto
    char descricao[100];                // Descrição detalhada
    float preco;                        // Preço unitário
    int quantidade;                     // Estoque disponível
    char categoria[30];                 // Categoria (bebida, lanche, etc)
    int ativo;                          // Status (1=ativo, 0=inativo)
};
```

### Estrutura `Pedido`
```c
struct Pedido {
    int id;                             // ID do pedido
    char cpf_cliente[11];               // CPF do cliente
    char nome_restaurante[50];          // Nome do restaurante
    struct ItemCarrinho itens[50];      // Itens do pedido
    int num_itens;                      // Quantidade de itens
    float valor_total;                  // Valor total
    struct Endereco endereco_entrega;   // Endereço de entrega
    char forma_pagamento[20];           // PIX, Dinheiro, Cartão
    char status[30];                    // Status do pedido
    char data_hora[20];                 // Data/hora da criação
    int visualizacoes;                  // Número de visualizações
    time_t timestamp_criacao;           // Timestamp UNIX
};
```

### Estrutura `Carrinho`
```c
struct Carrinho {
    struct ItemCarrinho itens[50];      // Array de itens
    int num_itens;                      // Quantidade de itens
    float valor_total;                  // Total dos produtos
    float taxa_entrega;                 // Taxa de entrega
    char nome_restaurante[50];          // Restaurante do pedido
};
```

---

## 🔄 Fluxo de Execução

### 1. Inicialização do Sistema
```
main() → configurarAcentuacao() → Inicialização de Structs → Loop Principal
```

### 2. Fluxo de Autenticação
```
Menu Principal → Cadastro/Login → Validação de Dados → Modo de Usuário
```

### 3. Fluxo do Cliente
```
Modo Cliente → Listar Restaurantes → Ver Cardápio → Adicionar ao Carrinho
           → Finalizar Pedido → Selecionar Pagamento → Confirmar Pedido
```

### 4. Fluxo do Restaurante
```
Modo Restaurante → Dashboard → Gerenciar Produtos → Ver Pedidos
               → Atualizar Status → Configurações
```

### Diagrama de Navegação

```
┌─────────────────┐
│  Menu Principal │
└────────┬────────┘
         │
    ┌────┴────┐
    │         │
┌───▼───┐ ┌──▼──┐
│Cadastro│ │Login│
└───┬───┘ └──┬──┘
    └────┬───┘
         │
    ┌────▼─────────┐
    │Seleção de Modo│
    └────┬─────────┘
         │
    ┌────┴────┬────────────┐
    │         │            │
┌───▼────┐ ┌─▼──────┐ ┌───▼─────┐
│Cliente │ │Restaurante│ │Entregador│
└───┬────┘ └─┬──────┘ └───┬─────┘
    │         │            │
┌───▼────────────┐ ┌──────▼──────────┐
│• Ver Restaurantes│ │• Dashboard      │
│• Fazer Pedido   │ │• Gerenciar Produtos│
│• Favoritos      │ │• Ver Pedidos    │
│• Perfil         │ │• Configurações  │
└─────────────────┘ └─────────────────┘
```

---

## 👥 Organização do Desenvolvimento

### Metodologia de Trabalho

#### 1. **Controle de Versão**
- **Ferramenta**: Git + GitHub
- **Branch principal**: `main`
- **Workflow**: Commits diretos após validação local
- **Commits**: Mensagens descritivas em português

#### 2. **Divisão de Tarefas**
O desenvolvimento foi organizado por funcionalidades:

| Desenvolvedor | Responsabilidades Principais |
|---------------|------------------------------|
| **Kaio Vítor** | • Estrutura geral do projeto<br>• Sistema de autenticação<br>• Integração Git/GitHub<br>• Documentação |
| **Matheus Souza** | • Interface do cliente<br>• Sistema de carrinho<br>• Finalização de pedidos<br>• Sistema de favoritos |
| **Macio Alves** | • Interface do restaurante<br>• Gerenciamento de produtos<br>• Sistema de pedidos<br>• Horários de funcionamento |

#### 3. **Fluxo de Desenvolvimento**
```
1. Definição da Feature
2. Implementação Local
3. Testes Manuais
4. Commit + Push
5. Review em Grupo
6. Ajustes se necessário
```

#### 4. **Comunicação**
- **Reuniões**: Síncronas para alinhamento
- **Git**: Para rastreamento de alterações
- **Comentários no código**: Para documentação inline

---

## 📏 Padrões e Convenções

### Nomenclatura de Funções

#### Funções de Interface (UI)
```c
void nome_da_tela_ui();          // Exemplo: menu_ui(), login_ui()
```
- Sufixo `_ui` indica função de interface
- Nome descritivo da tela/funcionalidade

#### Funções de Menu
```c
int menu_nome_contexto();        // Exemplo: menu_cliente(), menu_carrinho()
```
- Prefixo `menu_` indica função de navegação
- Retorna opção selecionada (int)

#### Funções de Lógica
```c
tipo nome_acao();                // Exemplo: cadastro(), logar(), adicionar_item_carrinho()
```
- Nome descritivo da ação
- Sem sufixo especial

### Nomenclatura de Variáveis

```c
// Structs: PascalCase
struct Cliente cliente;
struct Produto produtos[100];

// Variáveis simples: snake_case
int num_produtos;
float valor_total;
char nome_restaurante[50];

// Arrays: plural
struct Pedido pedidos[100];
struct ItemCarrinho itens[50];
```

### Estrutura de Funções UI

```c
void nome_ui() {
    clearScreen();              // 1. Limpa a tela
    
    // 2. Exibe cabeçalho/título
    printf("╔════════════════════════════════╗\n");
    printf("║       TÍTULO DA TELA           ║\n");
    printf("╚════════════════════════════════╝\n");
    
    // 3. Exibe conteúdo
    printf("\n  Opções:\n");
    printf("  [1] Opção 1\n");
    printf("  [2] Opção 2\n");
    
    // 4. Solicita input (se necessário)
    printf("\n  Escolha: ");
}
```

### Tratamento de Entrada

```c
// Limpeza de buffer após scanf
scanf("%d", &opcao);
limparBuffer();

// Uso de fgets para strings (evita buffer overflow)
fgets(nome, sizeof(nome), stdin);
nome[strcspn(nome, "\n")] = '\0';  // Remove \n
```

### Uso de Comentários

```c
// Comentários de seção
// =====================================================
// MÓDULO: Gerenciamento de Produtos
// =====================================================

// Comentários de função
/*
 * Função: cadastrar_produto_ui
 * Descrição: Interface para cadastro de novos produtos
 * Parâmetros: produtos[] - array de produtos
 *             num_produtos - ponteiro para contador
 */

// Comentários inline (quando necessário)
if (opcao == 1) {  // Opção de adicionar ao carrinho
    adicionar_ao_carrinho_ui(&carrinho, produtos, num_produtos);
}
```

---

## 🔍 Módulos Funcionais

### Módulo de Autenticação
- **Arquivos**: Linhas 600-1000
- **Funções principais**:
  - `cadastro()`: Cadastro de novos usuários
  - `logar()`: Login de usuários existentes
  - `le_valida_verificacao()`: Código de verificação
  - `alterar_senha()`: Alteração de senha

### Módulo de Cliente
- **Arquivos**: Linhas 1000-2000
- **Funções principais**:
  - `modo_cliente_ui()`: Interface principal
  - `adicionar_ao_carrinho_ui()`: Gestão do carrinho
  - `finalizar_compra_ui()`: Checkout
  - `adicionar_produto_favorito_ui()`: Favoritos

### Módulo de Restaurante
- **Arquivos**: Linhas 2000-3000
- **Funções principais**:
  - `restaurante_dashboard_ui()`: Dashboard
  - `cadastrar_produto_ui()`: Cadastro de produtos
  - `restaurante_pedidos_ui()`: Visualização de pedidos
  - `gerenciar_status_pedido()`: Atualização de status

### Módulo de Pedidos
- **Arquivos**: Linhas 3000-3500
- **Funções principais**:
  - `inicializar_carrinho()`: Inicialização
  - `adicionar_item_carrinho()`: Adicionar item
  - `remover_item_carrinho()`: Remover item
  - `calcular_total_carrinho()`: Calcular total

### Módulo de Interface
- **Arquivos**: Linhas 3500-4600
- **Funções principais**:
  - Todas as funções `*_ui()`
  - `clearScreen()`: Limpa tela
  - `limparBuffer()`: Limpa buffer de entrada
  - `configurarAcentuacao()`: Configura UTF-8

---

## 🧪 Testes e Validação

### Estratégia de Testes
1. **Testes Manuais**: Execução e navegação por todos os fluxos
2. **Validação de Entrada**: Verificação de dados inválidos
3. **Testes de Integração**: Fluxos completos (cadastro → pedido → finalização)
4. **Testes de Persistência**: Verificação de salvamento/carregamento

### Cenários de Teste Principais
- ✅ Cadastro e login de cliente
- ✅ Cadastro e login de restaurante
- ✅ Adicionar produtos ao carrinho
- ✅ Finalizar pedido completo
- ✅ Gerenciar status de pedidos
- ✅ Sistema de favoritos
- ✅ Horários de funcionamento

---

## 📊 Métricas do Projeto

| Métrica | Valor |
|---------|-------|
| **Linhas de Código** | ~4.600 |
| **Número de Structs** | 9 |
| **Número de Funções** | ~150+ |
| **Funções de UI** | ~80+ |
| **Funções de Lógica** | ~70+ |
| **Tempo de Desenvolvimento** | ~6 semanas |

---

## 🚀 Próximos Passos / Melhorias Futuras

### Melhorias Planejadas
- [ ] Separar código em múltiplos arquivos (.h e .c)
- [ ] Implementar persistência completa em arquivos
- [ ] Adicionar validações mais robustas
- [ ] Implementar busca de restaurantes/produtos
- [ ] Sistema de avaliações e comentários
- [ ] Histórico completo de pedidos
- [ ] Relatórios para restaurantes

### Refatorações Sugeridas
- [ ] Modularizar o código em arquivos separados
- [ ] Criar biblioteca de funções auxiliares
- [ ] Implementar gerenciamento de memória dinâmica
- [ ] Adicionar tratamento de erros mais robusto
- [ ] Documentar todas as funções com Doxygen

---

## 📚 Referências e Recursos

### Documentação Utilizada
- **Linguagem C**: [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- **Git**: [Pro Git Book](https://git-scm.com/book/pt-br/v2)
- **Markdown**: [GitHub Markdown Guide](https://guides.github.com/features/mastering-markdown/)

### Ferramentas
- **Compilador**: GCC (GNU Compiler Collection)
- **Editor**: VS Code / Dev-C++
- **Controle de Versão**: Git + GitHub
- **Terminal**: Linux/Windows Terminal

---

<div align="center">

## 📝 Notas para Apresentação

Este documento serve como guia completo para a apresentação do projeto ao professor. Ele cobre:

✅ **Estrutura técnica** do código
✅ **Organização da equipe** e divisão de tarefas
✅ **Arquitetura** e design do sistema
✅ **Fluxos** de execução e navegação
✅ **Padrões** e convenções adotados
✅ **Métricas** e resultados alcançados

---

**Universidade Católica de Brasília (UCB)**

Disciplina: Algoritmos e Programação Estruturada

Equipe: [Kaio Veras](https://github.com/KaioVeras) • [Matheus Souza](https://github.com/Matheus-Souza-Silva) • [Macio Alves](https://github.com/Marcola22dev)

</div>
