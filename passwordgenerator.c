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

    int savePassword(char *mPass, char *newPassword, char *description)
    {
        sqlite3 *db;
	sqlite3_stmt *stmt;
	const char url[25] = "sqlite/passwords";
        int rc = sqlite3_open(url, &db);
	char *errMsg = (char *) malloc(sizeof(char) * 100);
	const char sqlStmt[100] = "INSERT INTO userPassword (password, description) VALUES (?, ?) WHERE masterPassword=?";

	if (rc != SQLITE_OK)
	{
	    printf("SQL error: can't connect to database.\n");
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
	        sqlite3_bind_text(stmt, 1, mPass, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, newPassword, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, description, -1, SQLITE_STATIC);
		rc = sqlite3_step(stmt);

		if(rc != SQLITE_DONE)
		{
		    printf("SQL error: %s\n", errMsg);
		    return 1;
		}
		else
		{
		    printf("Password added.\n");
		    return 0;
		}
	    }
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	free(errMsg);
    }
   
