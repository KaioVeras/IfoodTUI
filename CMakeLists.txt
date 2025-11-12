cmake_minimum_required(VERSION 4.0)
project(IfoodTUI C)

set(CMAKE_C_STANDARD 11)

# 1. Adicione o executável e liste APENAS os arquivos .c
add_executable(IfoodTUI
        src/main.c
        src/screens/cadastro.c
        src/screens/login.c
        src/screens/welcome.c
        src/utils/clear.c
)

# 2. Diga ao seu executável onde procurar os headers (.h)
# Usar "src" como base permite que #include "includes/screens.h" funcione
target_include_directories(IfoodTUI PUBLIC src)