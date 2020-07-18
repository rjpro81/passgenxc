
#ifndef SESSIONMANAGERHEADER
#define SESSIONMANAGERHEADER

extern int masterLoginStatus;
extern int loginStatus;

struct SessionManager;

char * getSessionUser(void);

char getSessionStatus(void);

int logoff(void);

int login(const char *username, const char *password);

int masterLogin(const char *masterPassword);

#endif

