#include "accountmanager.h"
#include "sessionmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
const char *ACCOUNTS_FILE = "accounts.csv";

int AddMasterPassword(void)
{
	printf("Enter a master password: ");
	char *masterPass = (char *)malloc(sizeof(char) * 100);
	scanf("%s", masterPass);
	printf("Confirm password: ");
	char *confirmMaster = (char *)malloc(sizeof(char) * 100);
	scanf("%s", confirmMaster);
	if(strcmp(masterPass, confirmMaster) == 0)
	{
		file = fopen("accounts.csv", "a");
        fputs(masterPass, file);
		fputs(",", file);

		free(masterPass);
	    free(confirmMaster);
	    free(file);
	    fclose(file);

		AddUserLogin(0);
	}
	else
	{
		printf("Passwords do not match!\n");
		return 1;
	}
	return 0;
}

int AddUserLogin(int status)
{
	if (status == 0)
	{
        printf("Enter username: ");
	    char *username = (char *)malloc(sizeof(char) * 100);
	    scanf("%s", username);
	    printf("Enter password: ");
	    char *password = (char *)malloc(sizeof(char) * 100);
	    scanf("%s", password);
	    printf("Confirm password: ");
	    char *confirmPass = (char *)malloc(sizeof(char) * 100);
	    scanf("%s", confirmPass);

		if(strcmp(password, confirmPass) == 0)
	    {
		    file = fopen("accounts.csv", "a");
            fputs(username, file);
		    fputs(",", file);
			fputs(password, file);
			fputs("\n", file);

			free(username);
		    free(password);
		    free(confirmPass);
		    free(file);
		    fclose(file);
	    }
	    else
	    {
		    printf("Passwords do not match!\n");
		    return 1;
	    }
	    return 0;
	}
	return 1;
}




