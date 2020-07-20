#include "accountmanager.h"
#include </home/ralph/passgenxc/sqlite/sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


sqlite3 *db;
char *errMsg;
int rc;
char *sqlStmt;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int createMasterPassword(const char *masterPass)
{
    rc = sqlite3_open("passwords", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	return SQLITE_ERROR;
    } 
    else
    {
        sqlStmt = "INSERT INTO masterPass (masterPassword) VALUES (";
	strcat(sqlStmt, masterPass);
	strcat(sqlStmt, ")");
	rc = sqlite3_exec(db, sqlStmt, callback, 0, &errMsg);
	sqlite3_free(errMsg);

	if(rc != SQLITE_OK)
	{
	    fprintf(stderr, "SQL error: %s\n", errMsg);
	    sqlite3_free(errMsg);
	    return SQLITE_ERROR;
	}
	else
	{
	    return SQLITE_OK;
	}
    }
    sqlite3_close(db);
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

    if (strcpy(masterPass, confirmMasterPass) == 0)
    {
        rc = createMasterPassword(masterPass);
        if (rc == 0)
	{
            fprintf(stdout, "Master password added.");
	}    
    }    
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

int getMasterPassword()
{
    rc = sqlite3_open("passwords", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	return SQLITE_ERROR;
    } 
    else
    {
        sqlStmt = "SELECT * FROM masterPass";
	rc = sqlite3_exec(db, sqlStmt, callback, 0, &errMsg);

	if(rc != SQLITE_OK)
	{
	    fprintf(stderr, "SQL error: %s\n", errMsg);
	    sqlite3_free(errMsg);
	    return SQLITE_ERROR;
	}
	else
	{
	    return SQLITE_OK;
	}
    }
    sqlite3_close(db);
}



