#ifndef USERS_H
#define USERS_H

typedef struct {
    char name[100];
    char email[100];
} User;

void loadUsersFromFile();
void findUserByName(const char *userName);
void addUserToFile(User user);

#endif
