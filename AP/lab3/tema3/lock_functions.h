#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h> // EACCES and errno

#include <stdlib.h> // exit()
#include <fcntl.h>// creat()

void err_sys(const char* x);

#define LOCKDIR ""
#define MAXINCERC 3
#define WAITTIME 5

bool lock(char *name);
void unlock(char *name);
char *lockpath(char *name);