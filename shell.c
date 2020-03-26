
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

char ** parse_args(char*buff);
void exec2();

int main(int argc, char *argv[]){


    exec2();
    return 0;
}

void exec2()
{
    char path[256];
    char command[256]="";
    int status;
    while (1)
    {

        getcwd(path,256);
        printf("%s ",path);

        fgets(command,256,stdin);
        command[strlen(command)-1]='\0';

        char **params=parse_args(command);

        pid_t pid=fork();
        if (pid < 0)
        {
            printf ("Unable to fork");
            continue;
        }
        if (pid !=0)
        {
            waitpid(pid, &status,0);
        }
        else
        {
            execvp (params[0], params);
            perror("");
            exit(-1);
        }
    }
}

char ** parse_args(char*buff)
{
    char **args=(char**)malloc(sizeof(char*));
    char *aux;
    int i=0;
    aux=strtok(buff," ");
    while(aux!=NULL)
    {
        args=(char**)realloc(args,i+2);
        args[i]=(char*)malloc(sizeof(char)*(strlen(aux)+1));
        strcpy(args[i],aux);
        aux=strtok(NULL," ");
        i++;
    }
    args[i]=NULL;
    return args;
}