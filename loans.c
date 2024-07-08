#include "loans.h"


#define MAX_BOOKS 100
#define MAX_LOANS 100

loan loans[MAX_LOANS];
int numLoans = 0;
int loanCount = 0;


void writeLoanToFile(loan loan) {
    FILE *file = fopen("loans.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s,%s,%s,%s,%d,%d\n", loan.title, loan.author, loan.borrowerFirstName, loan.borrowerLastName, loan.dueDate, loan.returned);
        fclose(file);
    }
}

int findBookInFile(char *title, char *author, book *book) {
    FILE *file = fopen("library.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char fileTitle[100], fileAuthor[100], fileType[50], fileLocation[50];
        int fileNumCopies;

        sscanf(line, "%99[^,],%99[^,],%49[^,],%49[^,],%d", fileTitle, fileAuthor, fileType, fileLocation, &fileNumCopies);
        if (strstr(fileTitle, title) != NULL && strstr(fileAuthor, author) != NULL) {
            strcpy(book->title, fileTitle);
            strcpy(book->author, fileAuthor);
            strcpy(book->type, fileType);
            strcpy(book->location, fileLocation);
            book->numCopies = fileNumCopies;
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void updateBookCopies(char *title, char *author, int newCopies) {
    FILE *file = fopen("library.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char fileTitle[100], fileAuthor[100], fileType[50], fileLocation[50];
        int fileNumCopies;
        sscanf(line, "%99[^,],%99[^,],%49[^,],%49[^,],%d", fileTitle, fileAuthor, fileType, fileLocation, &fileNumCopies);
        if (!found && strstr(fileTitle, title) != NULL && strstr(fileAuthor, author) != NULL) {
            fileNumCopies = newCopies;
            found = 1;
        }
        fprintf(tempFile, "%s,%s,%s,%s,%d\n", fileTitle, fileAuthor, fileType, fileLocation, fileNumCopies);
    }

    fclose(file);
    fclose(tempFile);

    remove("library.txt");
    rename("temp.txt", "library.txt");
}

void borrowBook(char *firstName, char *lastName) {
    printf("Borrow a book:\n");
    printf("Enter the book title:\n");
    char bookTitle[100];
    fgets(bookTitle, sizeof(bookTitle), stdin);
    removeSpaces(bookTitle);

    printf("Enter the author's name:\n");
    char bookAuthor[100];
    fgets(bookAuthor, sizeof(bookAuthor), stdin);
    removeSpaces(bookAuthor);

    book book;
    if (findBookInFile(bookTitle, bookAuthor, &book) == 0) {
        printf("No such book found.\n");
        return;
    }

    if (book.numCopies <= 0) {
        printf("This book is currently not available for borrowing.\n");
        return;
    }

    printf("Enter the number of days for borrowing:\n");
    int days;
    scanf("%d", &days);
    getchar();

    printBookBorrowed(bookTitle, days);
    updateBookCopies(bookTitle, bookAuthor, book.numCopies - 1);

    strcpy(loans[numLoans].title, bookTitle);
    strcpy(loans[numLoans].author, bookAuthor);
    strcpy(loans[numLoans].borrowerFirstName, firstName);
    strcpy(loans[numLoans].borrowerLastName, lastName);
    loans[numLoans].dueDate = days;
    loans[numLoans].returned = 0;
    numLoans++;

    writeLoanToFile(loans[numLoans - 1]);
}
void returnBook() {
    char bookTitle[100];
    printf("Enter the title of the book to return: ");
    fgets(bookTitle, sizeof(bookTitle), stdin);
    bookTitle[strcspn(bookTitle, "\n")] = 0;
    removeSpaces(bookTitle);

    int found = 0;

    for (int i = 0; i < numLoans; i++) {
        if (strcmp(loans[i].title, bookTitle) == 0 && !loans[i].returned) {
            found = 1;
            loans[i].returned = 1;

            book book;
            if (findBookInFile(bookTitle, loans[i].author, &book) != 0) {
                updateBookCopies(book.title, book.author, book.numCopies + 1);
            }
            break;
        }
    }

    printBookReturnStatus(bookTitle, found);
}

void viewLoans() {
    printf("Current Loans:\n");
    if (numLoans == 0) {
        printf("No books are currently on loan.\n");
    } else {
        for (int i = 0; i < numLoans; i++) {
            if (!loans[i].returned) {
                printLoanDetails(&loans[i]);
            }
        }
    }
}


void generateLoanDocument(loan currentLoan) {
    char fileName[100];
    sprintf(fileName, "%s_%s___loan.txt", currentLoan.borrowerFirstName, currentLoan.borrowerLastName);
    FILE *filePtr = fopen(fileName, "w");
    if (filePtr == NULL) {
        printf("Error opening the file for loan %s.\n", fileName);
        return;
    }
    fprintf(filePtr, "Loan details:\n");
    fprintf(filePtr, "Borrower: %s %s\n", currentLoan.borrowerFirstName, currentLoan.borrowerLastName);
    fprintf(filePtr, "Book: %s by %s\n", currentLoan.title, currentLoan.author);
    fprintf(filePtr, "Copies Borrowed: 1\n");
    fclose(filePtr);
    printf("Loan document generated for %s %s.\n", currentLoan.borrowerFirstName, currentLoan.borrowerLastName);
}





void handleFileError(const char *fileName) {
    printf("Error opening the file %s.\n", fileName);
}

void printLoanDetails(const loan *currentLoan) {
    printf("Title: %s\n", currentLoan->title);
    printf("Author: %s\n", currentLoan->author);
    printf("Borrower: %s %s\n", currentLoan->borrowerFirstName, currentLoan->borrowerLastName);
    printf("Due Date: %d\n", currentLoan->dueDate);
    printf("----------------------------\n");
}

void printBookReturnStatus(const char *bookTitle, int found) {
    if (found) {
        printf("Book '%s' returned successfully.\n", bookTitle);
    } else {
        printf("Error: Book '%s' has not been loaned.\n", bookTitle);
    }
}

void printBookBorrowed(const char *bookTitle, int days) {
    printf("The book %s has been borrowed for %d days.\n", bookTitle, days);
}
