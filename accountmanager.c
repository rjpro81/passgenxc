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
    char sqlStmt[120] = "INSERT INTO userLogin (userName, userPassword, mPasswordId) VALUES (?, ?, ?)";
    if (strcmp(password, confirmPass) == 0)
    {
        rc = sqlite3_open(url, &db);
        sqlite3_stmt *stmt;
        if(rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	    return 1;
	}
	else
	{
	    rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);

	    if(rc != SQLITE_OK)
	    {
	        printf("SQL error: %d\n", rc);
		return 1;
	    }
	    else
	    {
		char id[2] = "1";
	        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, id, -1, SQLITE_STATIC);
		rc = sqlite3_step(stmt);
                if (rc != SQLITE_DONE)
		{
		    printf("SQL error: %d\n", rc);
		    return 1;
		}
		else
		{
		    printf("Account created successfully.\n");
		    return 0;
		}
	    }
	}
    }
    else
    {
        printf("Passwords must be the same.\n");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int createMasterPassword(const char *masterPass)
{
    rc = sqlite3_open(url, &db);
    char sqlStmt[100] = "INSERT INTO masterPassword (mPassword) VALUES (?)";
    sqlite3_stmt *stmt;

    if (rc != SQLITE_OK)
    {
        printf( "Can't open database: %d\n", rc);
    } 
    else
    {
	rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);

	if(rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
	    sqlite3_bind_text(stmt, 1, masterPass, -1, SQLITE_STATIC);
	    rc = sqlite3_step(stmt);
	    if (rc != SQLITE_DONE)
	    {
	        printf("SQL error: %d - Record not added.\n", rc);
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

int accountLogin(char *username, char *password, int id)
{
    rc = sqlite3_open(url, &db);
    sqlite3_stmt *stmt;
    errMsg = (char *) malloc(sizeof(char) * 100);
    if (rc != SQLITE_OK)
    {
        printf("SQL error: %d\n", rc);
    }    
    else
    {
        char sqlStmt[100] = "SELECT * FROM userLogin WHERE userName=? AND userPassword=? AND mPasswordId=?";
	rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
            sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
	    sqlite3_bind_int(stmt, 3, id);
	    rc = sqlite3_step(stmt);
	    
	    if (rc !=  SQLITE_ROW)
	    {
	        printf("SQL error: %d\n", rc);
	    }
	    else
	    {
 	        if (sqlite3_column_int(stmt, 3) == id)
		{
		    printf("Login sucessful.\n");
		    changeSessionToLoggedIn(sqlite3_column_int(stmt, 0), username);
		    return 0;
		}
		else
		{
		    printf("SQL error: %d - Invalid login.\n", rc);
		}
	    }
	}
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(errMsg);
}

int deleteAccount(void)
{
    rc = sqlite3_open(url, &db);
    const char sqlStmt[30] = "DELETE FROM masterPassword";
    if(rc != SQLITE_OK)
    {
        printf("SQL error: %d\n", rc);
    }
    else
    {
        int result = sqlite3_exec(db, sqlStmt, NULL, NULL, &errMsg);
	if (result != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
	    printf("Account deleted.\n");
	    changeSessionToLoggedOff();
	}
    }
    sqlite3_close(db);
    free(errMsg);
}

int getUserId(char *username, char *password)
{
    rc = sqlite3_open(url, &db);
    const char sqlStmt[70] = "SELECT userId FROM userLogin WHERE username=? AND userPassword=?";
    sqlite3_stmt *stmt;
    int id;

    if(rc != SQLITE_OK)
    {
        printf("SQL error: %d\n", rc);
    }
    else
    {
        sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
	rc = sqlite3_step(stmt);

	if (rc != SQLITE_ROW)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
	    id = sqlite3_column_int(stmt, 0);
	    return id;
	}
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(errMsg);
}

int getUserPassword(int userId)
{
    rc = sqlite3_open(url, &db);
    const char sqlStmt[70] = "SELECT Password userPassword FROM userLogin WHERE userId=?";

    if(rc != SQLITE_OK)
    {
        printf("SQL error: %d\n", rc);
    }
    else
    {
        rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
	    sqlite3_bind_int(stmt, 1, userId);
	    rc = sqlite3_step(stmt);

	    if (rc != SQLITE_ROW)
	    {
	        printf("SQL error: %d\n", rc);
	    }
	    else
	    {
	        return sqlite3_column_int(stmt, 0);
	    }
	}
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(errMsg);
}

int getMasterId(char *mPass)
{
    rc = sqlite3_open(url, &db);
    const char sqlStmt[70] = "SELECT mPasswordId FROM masterPassword WHERE mPassword=?";

    if(rc != SQLITE_OK)
    {
        printf("SQL error: %d\n", rc);
    }
    else
    {
	rc = sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	    return 1;
	}
        else
	{
            sqlite3_bind_text(stmt, 1, mPass, -1, SQLITE_STATIC);

            rc = sqlite3_step(stmt);
	    if(rc != SQLITE_ROW)
	    {
	        printf("SQL error: %d\n", rc);
	    }
	    else
	    {
	        return sqlite3_column_int(stmt, 0);
	    }
	}
    }
    sqlite3_close(db);
    free(errMsg);
}



