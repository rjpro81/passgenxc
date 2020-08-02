#ifndef PASSWORDGENERATORHEADER
#define PASSWORDGENERATORHEADER


char* defaultLengthPassword(void);
char* variedLengthPassword(int);
int savePassword(int, char*, char*);
int getPasswords(void *, int, char **, char **);
int getPasswordsView(void);

#endif
