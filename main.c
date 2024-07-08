#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "users.h"
#include "books.h"
#include "loans.h"
#include "menu.h"

#include "utilities.h"
#define MAX_BOOKS 100
#define MAX_LOANS 100
#define MAX_NAME_LENGTH 100
#define MAX_COPIES 10
int main(int argc, char *argv[]) {
    int  option;
if (argc < 4) {
        printf("Usage: %s <action> <username> <password>\n", argv[0]);
        return 1;
    }

    const char *action = argv[1];
    const char *username = argv[2];
    const char *password = argv[3];

    int loggedIn = 0;

    if (strcmp(action, "login") == 0) {
        loginUser(username, password, &loggedIn);
    } else if (strcmp(action, "create") == 0) {
        createAccount(username, password);
    } else {
        printf("Invalid action. Use 'login' or 'create'.\n");
    }



    loadLibraryFromFile("library.txt");


    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];

    do {
    menu();
    printf("Select an option: ");
    scanf("%d", &option);
    clearInputBuffer();

    switch (option) {
    case 1:
        addBook();
        break;
    case 2:
        findBookByCriteria();
        break;
    case 3:
        borrowBook(username, password);
        break;
    case 4:
        returnBook();
        break;
    case 5:
        displayBooks();
        break;
    case 6:
        viewLoans();
        break;
    case 7:
        exitlib();
        break;
    default:
        printf("Invalid option. Please select again.\n");
    }

    waitForUserInput();
    clearScreen();

}
while (option != 7);

    return 0;
}
