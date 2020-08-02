#include "accountmanager.h"
#include "sessionmanager.h"
#include "passwordgenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    srand((unsigned) time(0));
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
	if(strcmp(argv[1], "-V") == 0)
	{
            getPasswordsView();	
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
		int mPasswordId = getMasterId(mPass);
	        printf("Enter username: \n");
	        char *username = (char *) malloc(sizeof(char) * 100);
	        scanf("%s", username);
	        printf("Enter password: \n");
	        char *password = (char *) malloc(sizeof(char) * 100);
	        scanf("%s", password);
                accountLogin(username, password, mPasswordId);
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
	if(strcmp(argv[1], "-g") == 0)
	{
           char *newPass = (char *) malloc(sizeof(char) * 100);
	   newPass = defaultLengthPassword();
	   printf("%s\n", newPass);
	   printf("\nDo you want to save password?(Y or N) ");
	   char savePasswordResponse[2];
	   scanf("%s", savePasswordResponse);
	   if(strcmp(savePasswordResponse, "N") == 0 || strcmp(savePasswordResponse, "n") == 0)
	   {
	       exit(0);
	   }
	   else if(strcmp(savePasswordResponse, "Y") == 0 || strcmp(savePasswordResponse, "y") == 0)
	   {
	       printf("What is the password description? ");
	       char pDescription[100];
	       scanf("%s", pDescription);
	       char *id = (char *) malloc(sizeof(char) * 20);
               id = getSessionUser();
               int userId = atoi(id);
	       savePassword(userId, newPass, pDescription);
	   }
	   else
	   {
	       exit(0);
	   }
	}
    }
    if(argc == 3)
    {
        if(strcmp(argv[1], "-G") == 0)
	{
	    int passwordLength = atoi(argv[2]);
	    if(passwordLength >= 8)
	    {
	        printf("%s\n", variedLengthPassword(passwordLength));
	    }
	    else
	    {
	        printf("Password length must be at least 8.\n");
	    }
	}
    }
    return 0;
}
