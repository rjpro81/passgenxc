
#include "sessionmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

int changeSessionToLoggedIn(int userId, char *username)
{
   file = fopen("/home/ralph/passgenxc/passgenxc/session.txt", "w");
   fprintf(file, "USER:%s\nID:%d\nSESSION:%d\n", username, userId, 1);
   fclose(file);

   return 0;
}

int changeSessionToLoggedOff(void)
{
    file = fopen("/home/ralph/passgenxc/passgenxc/session.txt", "w");
    fprintf(file, "USER:NULL\nID:%d\nSESSION:%d\n", -1, 0);
    fclose(file);

    return 0; 
}

char getSessionStatus(void)
{
    file = fopen("/home/ralph/passgenxc/passgenxc/session.txt", "r");
    char buff[100];
    fgets(buff, 100, file);
    char *status = (char *) malloc(sizeof(char) * 9);
    status = fgets(buff, 10, file);
    fclose(file);
   
    return status[8];
}

char* getSessionUser(void)
{
    file = fopen("/home/ralph/passgenxc/passgenxc/session.txt", "r");
    char buff[100];
    fgets(buff, 100, file);
    char *user = (char *) malloc(sizeof(char) * 100);
    char ch;

    while (ch=fgetc(file) != '\n')
    {
        strcat(user, &ch); 
    }
    char *sessionUser = (char *) malloc(sizeof(char) * strlen(user) + 1);
    for (int i = 3; i < strlen(user); i++)
    {
        strcat(sessionUser, &user[i]);
    }

    return sessionUser;
}

