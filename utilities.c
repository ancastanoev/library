#include "utilities.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeSpaces(char *str) {
    int i = 0, j = strlen(str) - 1;
    while (isspace(str[i]))
        i++;
    while (j >= 0 && (isspace(str[j]) || str[j] == '\n'))
        j--;
    str[j + 1] = '\0';
    if (i > 0)
        strcpy(str, str + i);
}
void waitForUserInput() {
    printf("\nPress ENTER to continue...");
    clearInputBuffer();
    getchar();
}
void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
