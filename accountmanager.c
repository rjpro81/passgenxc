#include "accountmanager.h"
#include </home/ralph/passgenxc/sqlite/sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


sqlite3 *db;
char *errMsg;
int rc;
char *sqlStmt;
sqlite3_stmt *stmt;
char url[50] = "/home/ralph/passgenxc/sqlite/passwords";

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

int createLogin(char *mPass)
{
    printf("Enter username: \n");
    char *username = (char *) malloc(sizeof(char) * 100);
    scanf("%s", username);
    printf("Enter password: \n");
    char *password = (char *) malloc(sizeof(char) * 100);
    scanf("%s", password);
    printf("Enter password again: \n");
    char *confirmPass = (char *) malloc(sizeof(char) * 100);
    scanf("%s", confirmPass);

    if (strcmp(password, confirmPass) == 0)
    {
        printf("Passwords are the same.\n");
    }
}

int createMasterPassword(const char *masterPass)
{
    rc = sqlite3_open(url, &db);
    errMsg = (char *) malloc(sizeof(char) * 100);
    char sqlStmt[80] = "INSERT INTO masterPass (masterPassword) VALUES (?)";
    sqlite3_stmt *stmt;

    if (rc != SQLITE_OK)
    {
        printf( "Can't open database: %s\n", sqlite3_errmsg(db));
	return 1;
    } 
    else
    {
	printf("%s\n", "Database opened.");
	rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);

	if(rc != SQLITE_OK)
	{
	    printf("SQL error: %s\n", errMsg);
	    return 1;
	}
	else
	{
	    sqlite3_bind_text(stmt, 1, masterPass, -1, SQLITE_STATIC);
	    rc = sqlite3_step(stmt);
	    if (rc != SQLITE_DONE)
	    {
	        printf("Error: record not added.\n");
		return 1;
	    }
	    else
	    {
	        printf("Master password added.\n");
	    }
	}
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int createAccount(void)
{
    int result = 1;
    printf("Enter a master password: ");
    char masterPass[50];
    scanf("%s", masterPass);
    printf("Enter master password again: ");
    char confirmMasterPass[50];
    scanf("%s", confirmMasterPass);

    if (strcmp(masterPass, confirmMasterPass) == 0)
    {
        result = createMasterPassword(masterPass);
        if (result == 0)
	{
	    int result = createLogin(masterPass);
	    return result;
	}
        else
	{
	    return 1;
	}	
    }
    else
    {
        printf("Passwords are not the same.\n");
	return 1;
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
    errMsg = (char *) malloc(sizeof(char) * 100);
    sqlStmt = (char *) malloc(sizeof(char) * 200);
    rc = sqlite3_open(url, &db);

    if (rc != SQLITE_OK)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return 1;
    } 
    else
    {
        sqlStmt = "SELECT * FROM masterPass";
	rc = sqlite3_exec(db, sqlStmt, callback, 0, &errMsg);

	if(rc != SQLITE_OK)
	{
	    printf("SQL error: %s\n", errMsg);
	    return 1;
	}
	else
	{
	    return 0;
	}
    }
    sqlite3_close(db);
}

int accountLogin(char *username, char *password)
{
    rc = sqlite3_open(url, &db);
    if (rc != SQLITE_OK)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return 1;
    }    
}



