
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint();

int main()
{

    struct sigaction sa_sigint;

    sa_sigint.sa_handler=&sigint; // atribui o handler que imprime a funcao a sa_sigint

    sigaction(SIGINT,&sa_sigint,NULL);//muda a acao quando recebe o sinal SIGINT
    for(;;); /* loop for ever */
    return 0;
}

void sigint()
{
    printf("Recebi um CTRL+c\n");
}
