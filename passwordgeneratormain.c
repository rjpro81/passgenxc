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
        if(strcmp(argv[1], "-c") == 0)
        {
	    createAccount();
        }
	if(strcmp(argv[1], "-v") == 0)
	{
	    printf("PassGenX: Password Generator (c) 2020 Ralph Julsaint\nversion 1.0\n");
	}
        if(strcmp(argv[1], "-h") == 0)
        {
            displayHelp();
        }
        if(strcmp(argv[1], "-l") == 0)
        {
	    if (getSessionStatus() == '0')
	    {
	        printf("Enter master password: \n");
		char *mPass = (char *) malloc(sizeof(char) * 100);
	        scanf("%s", mPass);
	        printf("Enter username: \n");
	        char *username = (char *) malloc(sizeof(char) * 100);
	        scanf("%s", username);
	        printf("Enter password: \n");
	        char *password = (char *) malloc(sizeof(char) * 100);
	        scanf("%s", password);
                accountLogin(username, password, mPass);
	    }
	    else
	    {
	        printf("You are already logged in.\n");
	    }
        }
	if(strcmp(argv[1], "-o") == 0)
	{
	    int result = changeSessionToLoggedOff();
	    if (result == 0)
	    {
	        printf("Logged off.\n");
	    }
	}
	if(strcmp(argv[1], "-D") == 0)
	{
	    deleteAccount();
	}
    }
    return 0;
}
