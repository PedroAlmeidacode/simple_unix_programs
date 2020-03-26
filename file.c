#include "/home/pedro/Desktop/auxilios/apue.h"



int
main()
{
char buf[MAXLINE]; /* from apue.h */
pid_t pid;
int status;
printf("%% "); /* print prompt (printf requires %% to print %) */
while (fgets(buf, MAXLINE, stdin) != NULL) {
if (buf[strlen(buf) - 1] == '\n')
buf[strlen(buf) - 1] = 0; /* replace newline with null */
if ((pid = fork()) < 0) {
printf("fork error");
} else if (pid == 0) { /* child */
execlp(buf, buf, (char *)0);
printf("couldn’t execute: %s", buf);
exit(127);
}
/* parent */
if ((pid = waitpid(pid, &status, 0)) < 0)
printf("waitpid error");
printf("%% ");
}
exit(0);
return 0;
}
