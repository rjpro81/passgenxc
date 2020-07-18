#ifndef ACCOUNTMANAGERHEADER
#define ACCOUNTMANAGERHEADER


struct AccountManager;

extern int masterPassId;

int createMasterPassword(const char *masterPass);

int createLogin(char *username, char *pass, char *mPass, int mPassId);

int createAccount(void);

int deleteAccount(char *username, char *password);

int deleteMasterAccount(char *mPass);

char* substring(char *str, int startIndex, int endIndex);

char* getMasterPassword();

#endif
