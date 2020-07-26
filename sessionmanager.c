
#include "sessionmanager.h"
#include <stdio.h>
#include <stdlib.h>

FILE *file;

int changeSessionToLoggedIn(char *username)
{
   file = fopen("/home/ralph/passgenxc/passgenxc/session.txt", "w");
   fprintf(file, "USER:%s\nSESSION:%d\n", username, 1);
   fclose(file);

   return 0;
}

int changeSessionToLoggedOff(void)
{
    file = fopen("/home/ralph/passgenxc/passgenxc/session.txt", "w");
    fprintf(file, "USER:NULL\nSESSION:%d\n", 0);
    fclose(file);

    return 0; 
}

char getSessionStatus(void)
{
    file = fopen("/home/ralph/passgenxc/passgenxc/session.txt", "r");
    char buff[100];
    fgets(buff, 100, file);
    char *status = (char *) malloc(sizeof(9));
    status = fgets(buff, 10, file);
    fclose(file);
   
    return status[8];
}
