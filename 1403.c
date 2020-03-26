#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
/* fork another process */
    pid = fork();
    if (pid < 0) { /* error occurred */
        printf("Fork Failed\n");
        exit(-1);
    } else if (pid == 0) { /* child process */
        execlp("/bin/ls", "ls", NULL);// 1st - ficheiro onde se encontra o segundo argumento , 2nd - argumento a executar , 3rd- o fim dos argumentos deve terminar em null
    } else { /* parent process */
/* parent waiting for the child to complete */
        waitpid(pid, NULL, 0);// espera pelo pid do filho no primeiro argumento ou seja espera que o pid do filho seja retornado ao pai significando que o filho terminou de executar
//status a null ,  e 0 opcoes a executar restantes 

        printf("Child Complete\n");
        exit(0);
    }
}
