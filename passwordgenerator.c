#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "sqlite3.h"
	 
    char charArray[71] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
	   'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 
	   'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
	   'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	   'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7',
	   '8', '9', '0', '!', '@', '#', '$', '(', '^', '&', ')','\0'};

    char defaultPasswordArray[8];
    char *variedLengthPasswordArray;    

    char* defaultLengthPassword(void)
    {
        for (int i = 0; i < sizeof(defaultPasswordArray); i++)
	{
	    int randomNum = (rand() % (69 - 0 + 1)) + 0;    
	    defaultPasswordArray[i] = charArray[randomNum];	    
	}
	return defaultPasswordArray;
    }
   
    char* variedLengthPassword(int passwordCount)
    {
	variedLengthPasswordArray = (char *) malloc(sizeof(char) * passwordCount + 1);
        for (int i = 0; i < passwordCount; i++)
        {
	   int randomNum = (rand() % (69 - 0 + 1)) + 0;
	   variedLengthPasswordArray[i] = charArray[randomNum]; 
	}	
	return variedLengthPasswordArray;
	free(variedLengthPasswordArray);
    }

    int savePassword(int userId, char *newPassword, char *description)
    {
        sqlite3 *db;
	sqlite3_stmt *stmt;
	const char url[25] = "sqlite/passwords";
        int rc = sqlite3_open(url, &db);
	const char sqlStmt[100] = "INSERT INTO userPasswords (Password, Description, userId) VALUES (?, ?, ?)";

	if (rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
            sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	    sqlite3_bind_text(stmt, 1, newPassword, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, description, -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 3, userId);

	    rc = sqlite3_step(stmt);

	    if(rc != SQLITE_DONE)
	    {
	        printf("SQL error: %d\n", rc);
		return 1;
	    }
		else
	    {
		printf("Password saved.\n");
		return 0;
	    }
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
    }

    int getPasswords(void *data, int argc, char **argv, char **col)
    {
        printf("*************************************************************\n");        
	for (int i = 0; i < argc; i++)
        {
            printf("%s\t", argv[i] ? argv[i] : "NULL");
        }
        printf("\n*************************************************************\n");        
        return 0;
    }

    int getPasswordsView(void)
    {
        sqlite3 *db;
	const char url[25] = "sqlite/passwords";
	int rc = sqlite3_open(url, &db);
	const char sqlStmt[35] = "SELECT * FROM userPasswords";
	char *errMsg = (char *) malloc(sizeof(char) * 100);
        
        if (rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
	    rc = sqlite3_exec(db, sqlStmt, getPasswords, NULL, &errMsg);
	    if (rc != SQLITE_OK)
	    {
	        printf("SQL error: %d\n", rc);
	    }
	    else
	    {
	        return 0;
	    }
	}
	sqlite3_close(db);
	free(errMsg);
    }

    int deletePassword(int id)
    {
        sqlite3 *db;
        const char url[25] = "sqlite/passwords";
        int rc = sqlite3_open(url, &db);
	const char sqlStmt[60] = "DELETE FROM userPasswords WHERE userPasswordId=?";
        sqlite3_stmt *stmt;

        if (rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
	    sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	    sqlite3_bind_int(stmt, 1, id);
	    rc = sqlite3_step(stmt);

	    if(rc != SQLITE_DONE)
	    {
	        printf("SQL error: %d\n", rc);
	    }
	    else
	    {
	        printf("Password deleted.\n");
	    }
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
    }

    void getPassword(char *description)
    {
        sqlite3 *db;
	const char url[25] = "sqlite/passwords";
	int rc = sqlite3_open(url, &db);
	const char sqlStmt[80] = "SELECT Password FROM userPasswords WHERE Description=?";
	sqlite3_stmt *stmt;
	const char *password = (char *) malloc(sizeof(char) * 100);
	password = "";

	if (rc != SQLITE_OK)
	{
	    printf("SQL error: %d\n", rc);
	}
	else
	{
	    sqlite3_prepare_v2(db, sqlStmt, -1, &stmt, NULL);
	    sqlite3_bind_text(stmt, 1, description, -1, NULL);
	    rc = sqlite3_step(stmt);

	    if(rc != SQLITE_ROW)
	    {
	        printf("SQL error: %d\n%s\n", rc, "No password found.");
	    }
	    else
	    {
	        password = sqlite3_column_text(stmt, 0);
		printf("***************************************************\n*%s\n***************************************************\n", password);
	    }
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
    }


   
