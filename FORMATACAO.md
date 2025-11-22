# Formatação de Código

Este projeto usa **clang-format** para manter a formatação consistente do código C.

## Instalação

### Windows
```bash
# Via Chocolatey
choco install llvm

# Via Scoop
scoop install llvm
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install clang-format
```

### macOS
```bash
brew install clang-format
```

## Como Usar

### Formatar um arquivo específico
```bash
clang-format -i main.c
```

### Formatar todos os arquivos .c e .h
```bash
# Linux/macOS
find . -name "*.c" -o -name "*.h" | xargs clang-format -i

# Windows (PowerShell)
Get-ChildItem -Recurse -Include *.c,*.h | ForEach-Object { clang-format -i $_.FullName }
```

### Verificar sem modificar
```bash
clang-format main.c | diff main.c -
```

## VS Code

Para formatar automaticamente no VS Code:

1. Instale a extensão "C/C++" da Microsoft
2. Adicione ao `settings.json`:
```json
{
  "editor.formatOnSave": true,
  "C_Cpp.clang_format_style": "file",
  "C_Cpp.formatting": "clangFormat"
}
```

## Atalhos no VS Code

- **Formatar documento**: `Shift + Alt + F` (Windows/Linux) ou `Shift + Option + F` (macOS)
- **Formatar seleção**: `Ctrl + K, Ctrl + F` (Windows/Linux) ou `Cmd + K, Cmd + F` (macOS)

## Configuração

O arquivo `.clang-format` na raiz do projeto define o estilo:
- Indentação: 7 espaços (tabs)
- Chaves: Estilo Allman (chaves em nova linha)
- Limite de coluna: 100 caracteres
- Ponteiros alinhados à direita: `int *ptr`

## EditorConfig

O arquivo `.editorconfig` garante configurações consistentes entre diferentes editores.
