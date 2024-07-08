#include "books.h"

book library[MAX_BOOKS];
int bookCount = 0;

void saveBookToFile(book book) {
    FILE *filePtr = fopen("library.txt", "a");
    if (filePtr == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(filePtr, "%s, %s, %s, %s, %d\n", book.title, book.author, book.type, book.location, book.numCopies);

    fclose(filePtr);
}

void addBook() {
    printf("Add a book:\n");
    printf("Enter necessary details:\n");

    printf("Enter the book title:\n");
    fgets(library[bookCount].title, sizeof(library[bookCount].title), stdin);
    removeSpaces(library[bookCount].title);

    printf("Enter the author's name:\n");
    fgets(library[bookCount].author, sizeof(library[bookCount].author), stdin);
    removeSpaces(library[bookCount].author);

    printf("Enter the book type:\n");
    fgets(library[bookCount].type, sizeof(library[bookCount].type), stdin);
    removeSpaces(library[bookCount].type);

    printf("Enter the book's location:\n");
    fgets(library[bookCount].location, sizeof(library[bookCount].location), stdin);
    removeSpaces(library[bookCount].location);

    printf("Enter the number of copies available:\n");
    scanf("%d", &library[bookCount].numCopies);
    clearInputBuffer();

    saveBookToFile(library[bookCount]);

    printf("The book %s has been added.\n", library[bookCount].title);

    bookCount++;
}

void displayBooks()
{
    printf("Books available in the library:\n");
    for (int i = 0; i < bookCount; i++)
    {
        if (library[i].numCopies > 0)
            printf("%d. Title: %s | Author: %s | Type: %s | Location: %s | Copies available: %d\n", i + 1, library[i].title, library[i].author, library[i].type, library[i].location, library[i].numCopies);
    }
}

void loadLibraryFromFile(const char *file)
{
    FILE *filePtr = fopen(file, "r");
    if (filePtr == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }
    while (fscanf(filePtr, "%99[^,],%99[^,],%99[^,],%99[^,],%d\n", library[bookCount].title, library[bookCount].author, library[bookCount].type, library[bookCount].location, &library[bookCount].numCopies) == 5)
        bookCount++;
    fclose(filePtr);
}
void findBookByCriteria()
{
    printf("Search for a book:\n");
    printf("Enter the search criteria:\n1. By title.\n2. By author.\n3. By title and author.\n");
    int criteria, i;
    scanf("%d", &criteria);
    getchar();
    if (criteria == 1)
    {
        char titleName[100];
        printf("Enter the book title:\n");
        fgets(titleName, sizeof(titleName), stdin);
        removeSpaces(titleName);
        printf("Books with title %s are:\n", titleName);
        for (i = 0; i < bookCount; i++)
            if (strstr(library[i].title, titleName) != NULL && library[i].numCopies > 0)
                printf("Title: %s | Author: %s | Type: %s | Location: %s | Copies available: %d\n", library[i].title, library[i].author, library[i].type, library[i].location, library[i].numCopies);
    }
    else if (criteria == 2)
    {
        char authorName[100];
        printf("Enter the author's name:\n");
        fgets(authorName, sizeof(authorName), stdin);
        removeSpaces(authorName);
        printf("Books written by the author %s are:\n", authorName);
        for (i = 0; i < bookCount; i++)
            if (strstr(library[i].author, authorName) != NULL && library[i].numCopies > 0)
                printf("Title: %s | Type: %s | Location: %s | Copies available: %d\n", library[i].title, library[i].type, library[i].location, library[i].numCopies);
    }
    else if (criteria == 3)
    {
        char titleName[100];
        char authorName[100];
        printf("Enter the book title:\n");
        fgets(titleName, sizeof(titleName), stdin);
        removeSpaces(titleName);
        printf("Enter the author's name:\n");
        fgets(authorName, sizeof(authorName), stdin);
        removeSpaces(authorName);
        printf("Books with title %s and author %s are:\n", titleName, authorName);
        for (i = 0; i < bookCount; i++)
            if (strstr(library[i].title, titleName) != NULL && strstr(library[i].author, authorName) != NULL && library[i].numCopies > 0)
                printf("Title: %s | Author: %s | Type: %s | Location: %s | Copies available: %d\n", library[i].title, library[i].author, library[i].type, library[i].location, library[i].numCopies);
    }
    else
        printf("Invalid search criteria.\n");
}
int findBook(char bookTitle[], char bookAuthor[])
{
    int i;
    for (i = 0; i < bookCount; i++)
    {
        if (stricmp(library[i].title, bookTitle) == 0 && stricmp(library[i].author, bookAuthor) == 0)
            return i;
    }
    return -1;
}
