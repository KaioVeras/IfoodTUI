# Compilador e flags
CC = gcc
CFLAGS = -Wall

# Diretórios
SRC_DIR = .
SCREENS_DIR = screens

# Busca automática de todos os arquivos .c
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SCREENS_DIR)/*.c)

# Nome do executável
OUT = ifood

# Regra padrão (compila se houver mudanças)
all: $(OUT)

# Compila automaticamente todos os .c
$(OUT): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Executa o programa (sempre recompila antes)
run: clean all
	./$(OUT)

# Remove o executável antigo
clean:
	rm -f $(OUT)
