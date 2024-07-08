#ifndef BOOKS_H
#define BOOKS_H

#include <stdio.h>

#define MAX_BOOKS 100
#define MAX_NAME_LENGTH 100
#define MAX_COPIES 10

typedef struct {
    char title[100];
    char author[100];
    char type[100];
    char location[100];
    int numCopies;
} book;

extern book library[MAX_BOOKS];
extern int bookCount;
void saveBookToFile(book book);
void addBook();
void displayBooks();
int findBook(char bookTitle[], char bookAuthor[]);
void loadLibraryFromFile(const char *file);
void findBookByCriteria();
#endif
