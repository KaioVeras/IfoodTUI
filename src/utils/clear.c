#include <stdlib.h>
#include "includes/utils.h"
/**
 * Implementação da função clearScreen
 */
void clearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
        system("clear");
    #elif defined(__unix__)
        system("clear");
    #endif
}