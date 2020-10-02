#ifndef PASSWORDGENERATORHEADER
#define PASSWORDGENERATORHEADER


char* defaultLengthPassword(void);
char* variedLengthPassword(int);
int savePassword(int, char*, char*);
int getPasswords(void *, int, char **, char **);
void getPassword(char *description);
int getPasswordsView(void);
int deletePassword(int);

#endif
