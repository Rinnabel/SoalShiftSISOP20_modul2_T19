#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc != 5) {
     printf("Masukin yang bener dong!\n");
     exit(EXIT_FAILURE);
  }

  struct tm t;
  time_t tm;

  pid_t pid, sid;
  pid = fork(); 
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

 while (1) {
    tm = time(NULL);
    t = *localtime(&tm);
    
    if ((t.tm_sec == atoi(argv[1])) || (strcmp(argv[1], "*") == 0) && (t.tm_min == atoi(argv[2])) || (strcmp(argv[2], "*") == 0) && (t.tm_hour == atoi(argv[3])) || (strcmp(argv[3], "*") == 0)) {

	if (fork() == 0) {
	   execl("/bin/bash", "bash", argv[4], NULL);
	   sleep(1);
	}
    }
  }
}

