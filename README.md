<div align="center">

# 🍛 IfoodTUI

### Clone do iFood com Interface de Texto (TUI) em C

[![Status](https://img.shields.io/badge/status-Completo-green)]((https://github.com/KaioVeras/IfoodTUI))
[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

[Sobre](#-sobre) • [Funcionalidades](#-funcionalidades) • [Tecnologias](#%EF%B8%8F-tecnologias) • [Como Executar](#-como-executar) • [Estrutura](#-estrutura-do-projeto) • [Contribuidores](#-contribuidores)

</div>

---

## 📖 Sobre

**IfoodTUI** é um projeto acadêmico desenvolvido para a disciplina de **Algoritmos e Programação Estruturada**, que simula um sistema de delivery de comida inspirado no iFood. O diferencial é a interface de usuário baseada em texto (TUI - Text User Interface), proporcionando uma experiência completa de pedidos através do terminal.

O sistema implementa três perfis de usuário: **Clientes**, **Restaurantes** e **Entregadores**, cada um com suas funcionalidades específicas, criando um ecossistema completo de delivery.

### 🎯 Objetivos do Projeto

- Aplicar conceitos de **programação estruturada** em C
- Trabalhar com **structs** complexas e gerenciamento de dados
- Implementar **persistência de dados** em arquivos
- Criar uma interface de usuário intuitiva no terminal
- Simular um sistema real de delivery de comida

---

## ✨ Funcionalidades

### 🔐 Sistema de Autenticação
- ✅ Login e cadastro de clientes
- ✅ Login e cadastro de restaurantes
- ✅ Validação de CPF e CNPJ
- ✅ Sistema de senhas

### 👤 Perfil do Cliente
- ✅ Visualizar restaurantes disponíveis
- ✅ Verificar horários de funcionamento
- ✅ Navegar pelo cardápio dos restaurantes
- ✅ Adicionar/remover itens do carrinho
- ✅ Sistema de favoritos (restaurantes e pratos)
- ✅ Gerenciar endereços de entrega
- ✅ Finalizar pedido com múltiplas formas de pagamento
- ✅ Acompanhar status do pedido em tempo real
- ✅ Histórico de pedidos

### 🍽️ Perfil do Restaurante
- ✅ Dashboard gerencial completo
- ✅ Cadastrar e editar produtos do cardápio
- ✅ Gerenciar estoque de produtos
- ✅ Definir categorias de produtos
- ✅ Configurar horário de funcionamento por dia da semana
- ✅ Visualizar e gerenciar pedidos recebidos
- ✅ Atualizar status dos pedidos
- ✅ Ativar/desativar produtos
- ✅ Sistema de métricas e visualizações

### 🛒 Sistema de Pedidos
- ✅ Carrinho de compras dinâmico
- ✅ Cálculo automático de totais e taxas
- ✅ Múltiplas formas de pagamento (PIX, Dinheiro, Cartão)
- ✅ Status dos pedidos: Recebido → Em Preparo → Saiu para Entrega → Entregue
- ✅ Timestamp de criação e rastreamento
- ✅ Persistência de pedidos em arquivo

### 🎁 Módulos Extras
- ✅ Catálogo de produtos com busca
- ✅ Sistema de fidelidade do restaurante
- ✅ Métricas de visualizações de pedidos

---

## 🛠️ Tecnologias

<div>

| Tecnologia | Descrição |
|------------|-----------|
| ![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white) | Linguagem de programação principal |
| **GCC** | Compilador GNU Compiler Collection |
| **MinGW** | Ambiente de desenvolvimento Windows |
| **Git** | Controle de versão |

</div>

### 📚 Bibliotecas Utilizadas
```c
#include <stdio.h>      // Entrada e saída padrão
#include <stdlib.h>     // Funções de utilidade geral
#include <string.h>     // Manipulação de strings
#include <time.h>       // Manipulação de data/hora
#include <locale.h>     // Suporte a localização e acentuação
#include <ctype.h>      // Funções de classificação de caracteres
```

---

## 🚀 Como Executar

### Pré-requisitos

- Compilador C (GCC, MinGW ou similar)
- Terminal com suporte a UTF-8 (para acentuação)
- Git (opcional, para clonar o repositório)

### Instalação e Execução

```bash
# Clone o repositório
git clone https://github.com/KaioVeras/IfoodTUI.git

# Entre no diretório do projeto
cd IfoodTUI

# Compile o projeto
gcc main.c -o ifoodtui

# Execute o programa
./ifoodtui
```

### No Windows (Dev-C++ ou MinGW)

```bash
# Compile
gcc main.c -o ifoodtui.exe

# Execute
ifoodtui.exe
```

### No Linux/Mac

```bash
# Compile com flags de otimização
gcc -Wall -O2 main.c -o ifoodtui

# Execute
./ifoodtui
```

---

## 📂 Estrutura do Projeto

```
IfoodTUI/
├── main.c                    # Código fonte principal
├── main                      # Executável compilado
├── README.md                 # Documentação do projeto
├── ESTRUTURA_PROJETO.md      # Detalhamento da estrutura
└── output/                   # Diretório de saída
```

### 🏗️ Arquitetura do Código

O projeto está organizado em:

- **Structs**: Definição de estruturas de dados (Cliente, Restaurante, Produto, Pedido, Carrinho)
- **Funções de UI**: Interfaces de texto para cada módulo
- **Funções de Lógica**: Processamento de dados e regras de negócio
- **Persistência**: Leitura e escrita em arquivos para salvar dados

---

## 👥 Contribuidores

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/KaioVeras">
        <img src="https://github.com/KaioVeras.png" width="100px;" alt="Kaio Veras"/><br>
        <sub><b>Kaio Vítor P. Veras</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Matheus-Souza-Silva">
        <img src="https://github.com/Matheus-Souza-Silva.png" width="100px;" alt="Matheus Souza"/><br>
        <sub><b>Matheus Souza Silva</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Marcola22dev">
        <img src="https://github.com/Marcola22dev.png" width="100px;" alt="Macio Alves"/><br>
        <sub><b>Macio Alves</b></sub>
      </a>
    </td>
  </tr>
</table>

---

## 📝 Licença

Este projeto é um trabalho acadêmico desenvolvido para fins educacionais.

---

## 🎓 Instituição

<div align="center">

**Universidade Católica de Brasília (UCB)**

Projeto desenvolvido como parte da disciplina de **Algoritmos e Programação Estruturada**

</div>

---

<div align="center">

**[⬆ Voltar ao topo](#-ifoodtui)**

</div>
