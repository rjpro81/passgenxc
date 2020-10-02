#ifndef ACCOUNTMANAGERHEADER
#define ACCOUNTMANAGERHEADER

int getLoginResult(void *data, int argc, char **argv, char **col);

int getPasswords(void *data, int argc, char **argv, char **col);

int getMasterId(char *mPass);

int getUserPassword(int userId);

int createMasterPassword(const char *masterPass);

int createLogin(char *mPass);

int createAccount(void);

int deleteAccount(void);

int accountLogin(char *username, char *password, int id);

char* substring(char *str, int startIndex, int endIndex);

#endif
