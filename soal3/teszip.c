#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){

  char *argv[] = {"unzip", "jpg.zip", NULL};
  execv("/usr/bin/unzip", argv);
}
