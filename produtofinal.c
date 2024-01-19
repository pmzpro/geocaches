#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

#define MAX_CODES 2000
#define MAX_LINE_LENGTH 1024


// Função (FoundP) para comparar duas caches e verificar se são iguais.
int compareCaches(const Cache *cache1, const Cache *cache2) {
    return strcmp(cache1->code, cache2->code);
}
// Limpa as caches da memória.
void clearGeocaches(int *geocacheCount) {
    *geocacheCount = 0;
    printf("\n\033[1;33mGeocaches cleared.\n\033[0m");
}
 
void getGeocaches(const char file[], Cache geocaches[], int *geocacheCount) {
    // Abre o arquivo no modo de leitura
    FILE *f = fopen(file, "r");
    if (!f) {
        printf("\n\033[1;31mFile could not be opened.\n\033[0m");
        return;
    }
 
    // Variáveis para armazenar a linha lida, o delimitador e os tokens
    char line[MAX_LINE_LENGTH];
    const char delimiter[] = ";";
 
    // Lê e descarta a linha de cabeçalho
    fgets(line, sizeof(line), f);
 
    // Loop para ler as linhas do arquivo e carregar as geocaches
    while (fgets(line, sizeof(line), f) && *geocacheCount < MAX_CODES) {
        // Inicializa uma nova estrutura Cache
        Cache gc = {0};
 
        // Tokeniza a linha usando o delimitador ";"
        char *token = strtok(line, delimiter);
 
        // Atribui os tokens às variáveis membros da estrutura Cache
        if (token) gc.code = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.name = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.state = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.owner = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.latitude = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.longitude = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.kind = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.size = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.difficulty = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.terrain = atof(token);
        token = strtok(NULL, delimiter);
        if (token) gc.status = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.hidden_date = strdup(token);
        token = strtok(NULL, delimiter);
        if (token) gc.founds = atoi(token);
        token = strtok(NULL, delimiter);
        if (token) gc.not_found = atoi(token);
        token = strtok(NULL, delimiter);
        if (token) gc.favourites = atoi(token);
        token = strtok(NULL, delimiter);
        if (token) gc.altitude = atoi(token);
 
        // Verifica se a geocache já existe no array antes de armazená-la
        int cacheExists = 0;
        for (int i = 0; i < *geocacheCount; i++) {
            if (compareCaches(&geocaches[i], &gc) == 0) {
                cacheExists = 1;
                break;
            }
        }
 
        // Se a geocache não existe, armazena-a no array
        if (!cacheExists) {
            geocaches[*geocacheCount] = gc;
            (*geocacheCount)++;
        }
    }
 
    // Fecha o arquivo após a leitura
    fclose(f);
 
    // Indica a quantidade de geocaches carregadas
    printf("\n\033[1;33m%d unique geocaches loaded.\n\033[0m", *geocacheCount);
}
// Mostra as geocaches que estão guardadas na memória (LOAD)
void printGeocacheDetails(const Cache cache, int index) {
    printf("\n\033[1;33mCache %d:\033[0m \n Code: %s, Name: %s, State: %s, Owner: %s, Latitude: %.6f, Longitude: %.6f, Kind: %s, Size: %s, Difficulty: %.1f, Terrain: %.1f, Status: %s, Hidden date: %s, Founds: %d, Not founds: %d, Favourites: %d, Altitude: %d\n",
        index + 1,
        cache.code,
        cache.name,
        cache.state,
        cache.owner,
        cache.latitude,
        cache.longitude,
        cache.kind,
        cache.size,
        cache.difficulty,
        cache.terrain,
        cache.status,
        cache.hidden_date,
        cache.founds,
        cache.not_found,
        cache.favourites,
        cache.altitude);
}

void listGeocaches(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;33mNo geocaches to display.\n\033[0m");
        return;
    }

    printf("\nListing all geocaches:\n");

    // Imprime os detalhes de cada cache e a percentagem de aparecimento
    for (int i = 0; i < geocacheCount; i++) {
        printGeocacheDetails(geocaches[i], i);

        
    }
}

// Função para listar geocaches com percentagem de aparecimento
void foundPGeocaches(const Cache geocaches[], int geocacheCount) {
    if (geocaches == NULL || geocacheCount == 0) {
        printf("\n\033[1;33mNo geocaches to display.\n\033[0m");
        return;
    }

    printf("\nListing all geocaches with percentage of appearance:\n");

    // Cria um array para contar as ocorrências de cada cache
    int occurrences[MAX_CODES] = {0};

    // Conta as ocorrências de cada cache
    for (int i = 0; i < geocacheCount; i++) {
        occurrences[i]++;
        for (int j = i + 1; j < geocacheCount; j++) {
            if (strcmp(geocaches[i].code, geocaches[j].code) == 0) {
                occurrences[i]++;
                occurrences[j]++;
            }
        }
    }

    // Imprime os detalhes de cada cache e a porcentagem de aparecimento
    for (int i = 0; i < geocacheCount; i++) {
        printGeocacheDetails(geocaches[i], i);

        // Calcula a porcentagem de aparecimento da cache
        float percentage = (float)geocaches[i].founds / (geocaches[i].not_found + geocaches[i].founds) * 100;
        printf("Percentage of appearance: %.2f%%\n", percentage);
    }
}




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
