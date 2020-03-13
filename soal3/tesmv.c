#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){

  char *argv[] = {"mv", "jpg/*/", "indomie"};
  execv("/bin/mv", argv);
}
