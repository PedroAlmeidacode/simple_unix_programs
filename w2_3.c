//
// Created by pedro on 28/02/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    printf("PID: %d\n",(int) getpid());
    printf("PPID: %d\n",(int) getppid());
    printf("UID: %d\n",(int) getuid());
    printf("GID: %d\n",(int) getgid());
    printf("Path: %s\n", getenv("PATH"));
    char buf[256]="";
    printf("%s\n",getcwd(buf,256));
    return 0;
}