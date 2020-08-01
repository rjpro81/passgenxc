#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
	 
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
   
