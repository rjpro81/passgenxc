#include "accountmanager.h"
#include "sessionmanager.h"
#include </home/ralph/passgenxc/passgenxc/sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

sqlite3 *db;
char *errMsg;
int rc;
sqlite3_stmt *stmt;
char url[50] = "/home/ralph/passgenxc/passgenxc/sqlite/passwords";

int getPasswords(void *data, int argc, char **argv, char **col)
{
    for (int i = 0; i < argc; i++)
    {
        printf("**************************************************\n%s\n**************************************************\n", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int getLoginResult(void *data, int argc, char **argv, char **col)
{
    int i;
    for (i = 1; i <= argc; i++)
    {
        
    }   
    printf("%d\n", i);
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
    free(errMsg);
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
    free(word);

    return str;
}

int getMasterPassword()
{
    errMsg = (char *) malloc(sizeof(char) * 100);
    rc = sqlite3_open(url, &db);

    if (rc != SQLITE_OK)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return 1;
    } 
    else
    {
        char sqlStmt[45] = "SELECT masterPassword FROM masterPass";
	rc = sqlite3_exec(db, sqlStmt, getPasswords, 0, &errMsg);

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
    free(errMsg);
}

int accountLogin(char *username, char *password, char *mPass)
{
    rc = sqlite3_open(url, &db);
    sqlite3_stmt *stmt;
    errMsg = (char *) malloc(sizeof(char) * 100);
    if (rc != SQLITE_OK)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return 1;
    }    
    else
    {
        char sqlStmt[100] = "SELECT * FROM userLogin WHERE userName=? AND userPassword=? AND masterPassword=?";
	rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
	    printf("SQL err: %s\n", errMsg);
	    return 1;
	}
	else
	{
            sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 3, mPass, -1, SQLITE_STATIC);
	    rc = sqlite3_step(stmt);
	    
	    if (rc !=  SQLITE_ROW)
	    {
	        printf("SQL error: %s\n", errMsg);
		return 1;
	    }
	    else
	    {
 	        if (strcmp(sqlite3_column_text(stmt, 2), mPass) == 0)
		{
		    printf("Login sucessful.\n");
		    changeSessionToLoggedIn(username);
		    return 0;
		}
		else
		{
		    printf("Invalid login.\n");
		    return 1;
		}
	    }
	}
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(errMsg);
}

int deleteAccount(char *mPass)
{
    rc = sqlite3_open(url, &db);
    char sqlStmt[50] = "DELETE FROM masterPass WHERE masterPassword=?";
    sqlite3_stmt *stmt;
    errMsg = (char *) malloc(sizeof(char) * 100);
    if(rc != SQLITE_OK)
    {
        printf("Error: could not connect to database.\n");
	return 1;
    }
    else
    {
       	rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
        if (rc != SQLITE_OK)
	{
	    printf("SQL error: %s\n", errMsg);
	    return 1;
	}	
        else
	{
	    sqlite3_bind_text(stmt, 1, mPass, -1, SQLITE_STATIC);
	    rc = sqlite3_step(stmt);
	    if(rc != SQLITE_DONE)
	    {
	        printf("SQL error: %s\n", errMsg);
		return 1;
	    }
	    else
	    {
	        printf("Account deleted.\n");
		return 0;
	    }
	}	
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(errMsg);
}



