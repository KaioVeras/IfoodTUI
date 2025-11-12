# Detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /f
    EXE = .exe
    RUN = $(OUT)$(EXE)
else
    RM = rm -f
    EXE =
    RUN = ./$(OUT)
endif

# Compiladores e flags
CC = gcc
WINCC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall

# Diretórios
SRC_DIR = .
SCREENS_DIR = screens

# Busca automática de todos os arquivos .c
SRC_FILES = $(wildcard $(SRC_DIR)/.c) $(wildcard $(SCREENS_DIR)/.c)

# Nomes dos executáveis
OUT = ifood
OUT_WIN = ifood.exe

# ------------------------------
# Regras principais
# ------------------------------

# Compila versão Linux ou Windows nativa
all: $(OUT)$(EXE)

$(OUT)$(EXE): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Compila versão Windows no Linux (cross-compilação)
windows:
	$(WINCC) $(CFLAGS) $(SRC_FILES) -o $(OUT_WIN)

# Executa o programa
run: all
	$(RUN)

# Limpa os binários
clean:
	-$(RM) $(OUT)$(EXE)
	-$(RM) $(OUT_WIN)