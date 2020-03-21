#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

 int main (int argc, char **argv){

   pid_t pid, sid;
   pid = fork();

   if (pid < 0){
     exit(EXIT_FAILURE);
   }
   if (pid > 0){
     exit(EXIT_SUCCESS);
   }

   sid = setsid
   if (sid < 0){
     exit(EXIT_FAILURE);
   }

   //Ngecek mode A apa B
   int mode;
   mode = getopt (argc, argv, "ab");
   switch (mode){
     case 'a':
     FILE *openfile;
     openfile = fopen("killer.c", "w");
     fprintf(openfile, "#include <unistd.h>\n#include <wait.h>\nint main(){\n
pid_t child_id = fork();\nif (child_id == 0){\nchar *argv[] = {\"pkill\", \"-9\", \"-s\", \"%d\", NULL};\n
execv(\"/usr/bin/pkill\", argv);\n}\nwhile(wait(NULL) > 0);\nchar *argv[] = {\"rm\", \"killer\", NULL};\n
execv(\"/bin/rm\", argv);\n}\n", sid);
     fclose(openfile);
     break;

     case 'b':
     FILE *openfile;
     openfile = fopen("killer.c", "w");
     fprintf(openfile, "#include <unistd.h>\n#include <wait.h>\nint main(){\n
pid_t child_id = fork();\nif (child_id == 0){\nchar *argv[] = {\"kill\", \"-9\", \"%d\", NULL};\n
execv(\"/bin/kill\", argv);\n}\nwhile(wait(NULL) > 0);\nchar *argv[] = {\"rm\", \"killer\", NULL};\n
execv(\"/bin/rm\", argv);\n}\n", getpid());
     fclose(openfile);
     break;

     default:
     printf("Mode tidak tersedia");
     return 0;
}


pid = fork();
if (pid == 0) {
  char *argv[] = {"gcc", "killer.c", "-o", "killer", NULL};
  execv("/usr/bin/gcc", argv);
}
  while(wait(NULL) > 0);
  pid = fork();
  if (pid == 0) {
  char *argv[] = {"rm", "killer.c", NULL};
  execv("/bin/rm", argv);
}

while(wait(NULL) > 0);

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

while (1) {
  pid_t child_id;
  child_id = fork();

    if (child_id == 0){
      //timestamp
      time_t timer;
      char buffer[26];
      struct tm* tm_info;
      timer = time(NULL);
      tm_info = localtime(&timer);
      strftime(buffer, 26, "%Y-%m-%d_%H:%M:%S", tm_info);

      char *argv[] = {"mkdir", buffer, NULL};
      execv("/bin/mkdir", argv);
    }else{
      child_id = fork();
      if (child_id == 0){
      //looping 20x buat download gambar
      for(int i=1; i<=20; i++){

        child_id = fork();
        if (child_id ==0){

        time_t timer;
        char buffer_2[26];
        struct tm* tm_info;
        epoc = time(NULL);
        tm_info = localtime(&timer);
        strftime(buffer_2, 26, "%Y-%m-%d_%H:%M:%S", tm_info);
        sprintf(web, "https://picsum.photos/%ld", ((epoc%1000)+100));
        sprintf(path, "%s/%s", buffer, buffer_2);

        char *argv_download[]={"wget", "-O", path, web, NULL};
        execv("/bin/wget", argv_download);
      }else{
        while(wait(NULL) > 0);
          sleep(5);
      }
    }
    while(wait(NULL) > 0);
    child_id = fork();
    if (child_id == 0){

      char zip[100];
      sprintf(zip, "%s.zip", buffer);
      char *argv[] = {"zip", "-r", zip, buffer, NULL};
      execv("/usr/bin/zip", argv);
    }else{
      while(wait(NULL) > 0);
      char *argv[] = {"rm", "-r", buffer, NULL};
      execv("/bin/rm", argv);
    }
}
sleep(30);
}
}
