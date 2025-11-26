#!/bin/bash

# Script para instalar e configurar formatação de código C

echo "Instalando clang-format..."
sudo apt update
sudo apt install -y clang-format

echo "Verificando instalação..."
clang-format --version

echo "Configuração concluída!"
echo ""
echo "Para formatar seu arquivo, use:"
echo "  - Ctrl+Shift+I (formatar documento inteiro)"
echo "  - Ctrl+K Ctrl+F (formatar seleção)"
echo "  - O arquivo será formatado automaticamente ao salvar"