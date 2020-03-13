#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>

int main(){
  pid_t child_id;

  //ngecek pertama
  child_id = fork();
  if (child_id < 0){
    exit(EXIT_FAILURE);
}

  //child hasil fork pertama
  if (child_id == 0){
    char *argv[] = {"unzip", "jpg.zip", NULL};
    execv("/usr/bin/unzip", argv);
}else{
  while ((wait(NULL)) > 0);
  pid_t child_id;

  //ngecek fork ke-2
  child_id = fork();
  if (child_id < 0){
    exit(EXIT_FAILURE);
}

  //child hasil fork ke-2
  if (child_id == 0){
    char *argv[] = {"mkdir", "indomie", NULL};
    execv("/bin/mkdir", argv);
}else{
  while ((wait(NULL)) > 0);
  pid_t child_id;

  //ngecek fork ke-3
  child_id = fork();
  if (child_id < 0){
    exit(EXIT_FAILURE);
}

  //child hasil fork ke-3
  if (child_id == 0){
    sleep(5);
    char *argv[] = {"mkdir", "sedaap", NULL};
    execv("/bin/mkdir", argv);
}
else{
  while ((wait(NULL)) > 0);
  printf("Ekstrak dan buat folder selesai");
}
}
}
}
