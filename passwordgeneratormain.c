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
    if(strcmp(argv[1], "-createaccount") == 0)
    {
	int result = createAccount();
	if(result > 0)
	{
	    printf("Account added.\n");
	}
    }
    if(strcmp(argv[1], "-help") == 0)
    {
        displayHelp();
    }
    if(strcmp(argv[1], "-login") == 0)
    {
        char status = getSessionStatus();
        if(strcmp(&status, "1"))
        {
            printf("Enter master password: ");
	    char mPass[50];
	    scanf("%s", mPass);
	    printf("%s\n", mPass);
	    printf("%s\n", getMasterPassword());
	    if(strcmp(mPass, getMasterPassword()) == 0)
	    {
	        printf("The same\n");
	    } else
	    {
	        printf("Not the same\n");
	    }
        }
    }
    return 0;
}
