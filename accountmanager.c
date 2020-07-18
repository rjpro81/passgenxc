#include "accountmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AccountManager
{
    char *filename;
    FILE *fp;
};

int masterPassId = 0;

int createMasterPassword(const char *masterPass)
{
    struct AccountManager *accountManager = (struct AccountManager *) malloc(sizeof(struct AccountManager));
    accountManager->filename = (char *) malloc(sizeof(char *) * 100);
    accountManager->fp = (FILE *) malloc(sizeof(FILE *));
    strcpy(accountManager->filename, "masterpasswords.csv");
    accountManager->fp = fopen(accountManager->filename, "w");
    masterPassId = masterPassId + 1;
    char id[100];
    snprintf(id, 100, "%d", masterPassId);
    strcat(id, ",");
    strcat(id, masterPass);
    strcat(id, "\n");
    fputs(id, accountManager->fp);
    fclose(accountManager->fp);
    free(accountManager);

    return masterPassId;
}

int createAccount(void)
{
    int result = 0;
    printf("Enter a master password: ");
    char masterPass[50];
    scanf("%s", masterPass);
    printf("Enter master password again: ");
    char confirmMasterPass[50];
    scanf("%s", confirmMasterPass);

    if(strcmp(masterPass, confirmMasterPass) == 0)
    {
        result = createMasterPassword(masterPass);
	printf("Enter username: ");
	char username[50];
	scanf("%s", username);
	printf("Enter password: ");
	char password[50];
	scanf("%s", password);
	printf("Enter password again: ");
	char confirmPassword[50];
	scanf("%s", confirmPassword);
	
	if (strcmp(password, confirmPassword) == 0)
	{   
            struct AccountManager *accountManager = (struct AccountManager *) malloc(sizeof(struct AccountManager));
	    accountManager->filename = (char *) malloc(sizeof(char *) * 100);
	    strcpy(accountManager->filename, "login.csv");
	    accountManager->fp = (FILE *) malloc(sizeof(FILE *));
	    accountManager->fp = fopen(accountManager->filename, "w");
	    char loginCred[150];
	    char resultToString[50];
	    strcat(loginCred, username);
	    strcat(loginCred, ",");
	    strcat(loginCred, password);
	    strcat(loginCred, ",");
	    strcat(loginCred, masterPass);
	    strcat(loginCred, ",");
	    snprintf(resultToString, 50, "%d", result);
	    strcat(loginCred, resultToString);
	    strcat(loginCred, "\n");
	    fputs(loginCred, accountManager->fp);
	    fclose(accountManager->fp);
	    free(accountManager);
	}
    }
    return result;    
}


char* substring(char *str, int startIndex, int endIndex)
{
    char *word = (char *) malloc(sizeof(char) * 200);
    int a = 0;
    for(int i = startIndex + 1; i < endIndex; i++)
    {
        word[a] = str[i];
	a = a + 1;
    }
    str = word;

    return str;
}

char mPass[100];
char* getMasterPassword()
{
    FILE *fp = (FILE *) malloc(sizeof(FILE *));
    fp = fopen("masterpasswords.csv", "r");
    int ch = getc(fp);
    int i = 0;
    char character[100];
    int commaIndex;
    
    while(ch != EOF)
    {
        mPass[i] = (char) ch;
        ch = getc(fp);
	i = i + 1;
	if((char) ch == ',')
	{
	    commaIndex = i;
	}
    }

    char *word = substring(mPass, commaIndex, sizeof(mPass));
       
    return word;

    fclose(fp); 
}



