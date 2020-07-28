#ifndef ACCOUNTMANAGERHEADER
#define ACCOUNTMANAGERHEADER

static int callback(void *data, int argc, char **argv, char **azColName);

int createMasterPassword(const char *masterPass);

int createLogin(char *mPass);

int createAccount(void);

int deleteAccount(char *mPass);

int accountLogin(char *username, char *password, char *mPass);

int deleteMasterAccount(char *mPass);

char* substring(char *str, int startIndex, int endIndex);

int getMasterPassword(void);

#endif
