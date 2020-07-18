
#include "sessionmanager.h"
#include <stdio.h>
#include <stdlib.h>

char getSessionStatus(void)
{
    FILE *fp = (FILE *) malloc(sizeof(FILE *));
    fp = fopen("session.txt", "r");
    int ch = getc(fp);
    char buffer[20];
    int iter = 0;
    while (ch != EOF)
    {
	buffer[iter] = ch;
        ch = getc(fp);
	iter = iter + 1;
    }
    fclose(fp);

    return buffer[8];
}
