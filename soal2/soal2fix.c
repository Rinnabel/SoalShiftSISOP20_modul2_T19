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

   //Ngecek mode A apa B
   int mode;
   mode = getopt (argc, argv, "ab");
   switch (mode){
     case 'a':
     goto mode_a;
     break;

     case 'b':
     goto mode_b;
     break;
}

//Mode A
mode_a:
printf("berhasil");

// Variabel untuk menyimpan PID
pid_t pid, sid;

// Menyimpan PID dari Child Process
pid = fork();

/* Keluar saat fork gagal
* (nilai variabel pid < 0) */
if (pid < 0){
  exit(EXIT_FAILURE);
}

/* Keluar saat fork berhasil
* (nilai variabel pid adalah PID dari child process) */
if (pid > 0) {
  exit(EXIT_SUCCESS);
}

umask(0);

sid = setsid();
if (sid < 0) {
  exit(EXIT_FAILURE);
}

if ((chdir("/home/czul/Desktop")) < 0) {
  exit(EXIT_FAILURE);
}

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

while (1) {
  pid_t child_id_d;

    child_id_d = fork();

    printf("Ini akan kepanggil 2 kali\n");

    if(child_id_d != 0){
      //timestamp
      time_t timer;
      char buffer[26];
      struct tm* tm_info;
      timer = time(NULL);
      tm_info = localtime(&timer);
      strftime(buffer, 26, "%Y-%m-%d_%H:%M:%S", tm_info);
      //printf("%s", buffer);

      char *argv[]={"mkdir", buffer, NULL};
      execv("/bin/mkdir", argv);
    }else {
      //nunggu folder dibuat
      while ((wait(NULL)) > 0);
      //looping 20x buat download gambar
      for(int i=1; i<=20; i++){

        //timestamp
        time_t timer;
        char buffer[26];
        struct tm* tm_info;
        timer = time(NULL);
        tm_info = localtime(&timer);
        strftime(buffer, 26, "%Y-%m-%d_%H:%M:%S", tm_info);
        int size = ( (unsigned long)time(NULL) % 1000 ) + 100;

        char *argv_download[]={"wget", "-o", buffer, web};
        execv("/bin/wget", argv_download);

      sleep(5);
      }
      printf("\nChild process.\nPID: %d, Parent's PID: %d\n", (int)getpid(), (int)getppid());
    }


sleep(30);
}

//Mode B
mode_b:
printf("berhasil");
}
