#ifndef LOAN_H
#define LOAN_H

#include "books.h"

#define MAX_LOANS 100


typedef struct {
    char title[100];
    char author[100];
    char borrowerFirstName[MAX_NAME_LENGTH];
    char borrowerLastName[MAX_NAME_LENGTH];
    int dueDate;
    int returned;
} loan;

extern loan loans[MAX_LOANS];
extern int numLoans;

void borrowBook(char *firstName, char *lastName);
void returnBook();
void viewLoans();
void updateBookCopies(char *title, char *author, int newCopies) ;
void generateLoanDocument(loan currentLoan);
void writeLoanToFile(loan currentLoan);
int findBookInFile(char *title, char *author, book *book);
void handleFileError(const char *fileName) ;
void printLoanDetails(const loan *currentLoan);
void printBookReturnStatus(const char *bookTitle, int found);
void printBookBorrowed(const char *bookTitle, int days);
#endif
