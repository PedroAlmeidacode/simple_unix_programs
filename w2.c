//
// Created by pedro on 28/02/20.
//

#include <stdio.h>
#include <unistd.h>

int main(){
    printf("The user ID is %d\n",(int)getuid());
    printf("The group id of the calling process is %d\n",(int) getppid());
    printf("The process ID is %d\n",(int)getpid());
    printf("The parent process ID is %d\n",(int) getppid());
    return 0;
}