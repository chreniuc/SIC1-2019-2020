#include "lock_functions.h"

void err_sys(const char* x) 
{ 
    perror(x); 
    exit(1); 
}

bool lock(char *name) {
  char *path;
  int fd, incerc;
  //extern int errno;
  path = lockpath(name); /* genereaza nume semafor */
  incerc = 0;
  while ((fd = creat(path, 0)) < 0 && errno == EACCES) {
    if (++incerc >= MAXINCERC)
      return false;
    sleep(WAITTIME);
  }
  if (fd < 0 || close(fd) < 0)
  {
    err_sys("lock");
  }
  return true;
}

void unlock(char *name) {
  if (unlink(lockpath(name)) < 0)
    err_sys("unlock");
}

char *lockpath(char *name) {
  static char path[70]; // char *strcat(); 
  strcpy( path, LOCKDIR );   
  return(strcat( path, name ));  }