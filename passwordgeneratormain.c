#include "accountmanager.h"
#include "sessionmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayHelp(void)
{
    FILE *fp = (FILE *) malloc(sizeof(FILE *));
    fp = fopen("help.txt", "r");
    int iter = 0;
    int ch = getc(fp);
    while (ch != EOF)
    {
	iter = iter + 1;
        putchar(ch);
	ch = getc(fp);
    }
    fclose(fp);
}

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        displayHelp();
    }
    if(argc == 2)
    {
        if(strcmp(argv[1], "-createaccount") == 0)
        {
	    createAccount();
        }
        if(strcmp(argv[1], "-view") == 0)
        {
            getMasterPassword();
        }
        if(strcmp(argv[1], "-help") == 0)
        {
            displayHelp();
        }
        if(strcmp(argv[1], "-login") == 0)
        {
	    printf("Enter username: \n");
	    char *username = (char *) malloc(sizeof(char) * 100);
	    scanf("%s", username);
	    printf("Enter password: \n");
	    char *password = (char *) malloc(sizeof(char) * 100);
	    scanf("%s", password);
            accountLogin(username, password);
        }
    }
    return 0;
}
