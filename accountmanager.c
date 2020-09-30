#include "accountmanager.h"
#include "sessionmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int rc;
FILE **file;
const char *LOGIN_FILE = "login.xml";
const char *XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>";

int getLoginResult(void *data, int argc, char **argv, char **col)
{
    int i;
    for (i = 1; i <= argc; i++)
    {
        
    }   
    printf("%d\n", i);
	return 0;
}

int createLogin(char *mPass)
{
    printf("Enter username: ");
    char *username = (char *) malloc(sizeof(char) * 100);
    scanf_s("%s", username, (unsigned)_countof(username));
    printf("Enter password: ");
    char *password = (char *) malloc(sizeof(char) * 100);
    scanf_s("%s", password, (unsigned)_countof(password));
    printf("Enter password again: ");
    char *confirmPass = (char *) malloc(sizeof(char) * 100);
    scanf_s("%s", confirmPass, (unsigned)_countof(confirmPass));
	
	if (strcmp(password, confirmPass) == 0)
	{
		fopen_s(file, LOGIN_FILE, "w");
		fputs(XML_HEADER, *file);
		const char *createLoginXMLString = "<Accounts>";
		strcat_s("\t<Account>", strlen(createLoginXMLString), createLoginXMLString);
		strcat_s("\t\t<Username>%s</Username>", strlen(createLoginXMLString), username);
		strcat_s("\t\t<Password>%s</Password>", strlen(createLoginXMLString), password);
		strcat_s("\t</Account>", strlen(createLoginXMLString), createLoginXMLString);
		strcat_s("</Accounts>", strlen(createLoginXMLString), createLoginXMLString);
		fputs(createLoginXMLString, *file);
	}
	else 
	{
		printf("Passwords do not match!\n");
	}
	fclose(*file);   
	return 0;
}//end CreateLogin()

int createMasterPassword(const char *masterPass)
{
	return 0;
}

int createAccount(void)
{
	return 0;
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
    free(word);

    return str;
}

int accountLogin(char *username, char *password, int id)
{
	return 0;
}

int deleteAccount(void)
{
	return 0;
}

int getUserId(char *username, char *password)
{
	return 0;
}

int getUserPassword(int userId)
{
	return 0;
}

int getMasterId(char *mPass)
{
	return 0;
}



