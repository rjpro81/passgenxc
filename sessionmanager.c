
#include "sessionmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
const char *SESSION_FILE = "session.xml";
char sessionUser[100];

int changeSessionToLoggedIn(int userId, char *username)
{
   fopen_s(file, SESSION_FILE, "w");
   fprintf(file, "USER:%s\nID:%d\nSESSION:%d\n", username, userId, 1);
   fclose(file);

   return 0;
}

int changeSessionToLoggedOff(void)
{
    fopen_s(file, SESSION_FILE, "w");
    fprintf(file, "USER:NULL\nID:%d\nSESSION:%d\n", -1, 0);
    fclose(file);

    return 0; 
}

int getSessionUserId(void)
{
    fopen_s(file, SESSION_FILE, "w");
    char buff[100];
    fgets(buff, 100, file);
    char id[50];
    fgets(id, 50, file);
    char *userId = (char *) malloc(sizeof(char) * 50);

    for(int i = 3; i < (int) strlen(id); i++)
    {
        strcat(userId, &id[i]);
    }

    return atoi(userId);
    free(userId);
}

char getSessionStatus(void)
{
    fopen_s(file, SESSION_FILE, "r");
    char buff[100];
    fgets(buff, 100, file);
    fgets(buff, 100, file);
    char *status = (char *) malloc(sizeof(char) * 9);
    status = fgets(buff, 10, file);
    fclose(file);
   
    return status[8];
    free(status);
}

char* getSessionUser(void)
{
    fopen_s(file, SESSION_FILE, "r");
    char *user = (char *) malloc(sizeof(char) * 100);   
    fgets(user, 100, file);
    
    int i = 5;
    while (i < (int) strlen(user))
    {
        printf("%c", user[i]);
	strcpy(sessionUser, &user[i]);
	i++;
    }
    
    return sessionUser;
    fclose(file);
    free(user);
}

