#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"



int main() {
    // Variaveis 
    Cache geocaches[MAX_CODES];
    int geocacheCount = 0;
    int menuOption;
    char file[256];



    do {
        // Menu Geocache
        printf("\033[1;32m\n******************************\033[0m");
        printf("\033[1;32m\n********* GEOCACHING *********\033[0m\n");
        printf("\033[1;32m******************************\033[0m\n");
        printf("\033[1;37m\n1 - LOAD\n2 - CLEAR\n3 - LIST\n4 - FOUNDP\n0 - QUIT\n\n\033[0m\033[1;32mChoose an option: \033[0m");
        scanf("%d", &menuOption);
        getchar(); // Limpa o buffer do teclado

        switch(menuOption) {
            case 1:
            //Função LOAD - lê o ficheiro e guarda os dados na memória.
                printf("\n\033[1;33mEnter filename: \033[0m");
                scanf("%255s", file);
                getGeocaches(file, geocaches, &geocacheCount); 
                break;
            case 2:
            //Função CLEAR - limpa os dados da memória.
                clearGeocaches(&geocacheCount);
                break;
            case 3:
            //Função LIST - mostra os dados que estão carregados na memória.
                listGeocaches(geocaches, geocacheCount);
                break;
            case 4:
            //Função FOUNP - mostra a percentagem de aparecimento da cache.
                foundPGeocaches(geocaches, geocacheCount);
                break;
            case 0:
            //Função QUIT - Termina o programa.
                printf("\n\033[1;31mExit Success!\033[0m\n");
                printf("\n");
                return EXIT_SUCCESS;
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (menuOption != 0); // O menu é apresentando até ser selecionada a opção 0 - Quit.

    
    return EXIT_SUCCESS;
}
