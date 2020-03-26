
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

const int PROCESSES = 6;
long factorial(int n);

int main()
{
    //array de numeros a factorizar
    int a[] = {1,2,5,7,9,12};
    //array que vai obter o resultado dos factoriais
    int res[] = {0,0,0,0,0,0};
    //6 pids
    pid_t pids[PROCESSES];
    int status;

    //imprime o array
    for (int i = 0; i < 6; i++) {
        printf("%d, ",a[i]);
    }
    printf("\n");






    //faz 6 forks
    for (int j = 0; j < PROCESSES; j++) {
        

        if ((pids[j] = fork()) == 0) { // processo filho
   		int x = (int) factorial(a[j]);
        	exit(x);
        } else if (pids[j] < 0) {

            	printf("Erro no fork !");
            	exit(0);
        } else {  // processo pai
		
            	wait(&res[j]);
		
        }
    }

        //imprime o array
        for (int i = 0; i < 6; i++) {
            printf("%d, ",res[i]);

        }
        printf("\n");

    return 0;
}


long factorial(int n) {
    int c;
    long r = 1;

    for (c = 1; c <= n; c++)
        r = r * c;

    return r;
}

