
#ifndef SESSIONMANAGERHEADER
#define SESSIONMANAGERHEADER

int changeSessionToLoggedIn(int userId, char *username);
int changeSessionToLoggedOff(void);
char getSessionStatus(void);
char * getSessionUser(void);

#endif

