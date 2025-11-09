# Compilador e flags
CC = gcc
WINCC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall

# Diretórios
SRC_DIR = .
SCREENS_DIR = screens

# Busca automática de todos os arquivos .c
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SCREENS_DIR)/*.c)

# Nomes dos executáveis
OUT = ifood
OUT_WIN = ifood.exe

# ------------------------------
# Regras principais
# ------------------------------

# Compila para Linux
all: $(OUT)

$(OUT): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Compila para Windows
windows: $(OUT_WIN)

$(OUT_WIN): $(SRC_FILES)
	$(WINCC) $(CFLAGS) $^ -o $@

# Executa no Linux
run: clean all
	./$(OUT)

# Executa o .exe pelo Wine (opcional)
run-win: windows
	wine $(OUT_WIN)

# Limpa os executáveis
clean:
	rm -f $(OUT) $(OUT_WIN)
