/*
O main program deve criar um array (input) com N valores distintos, e um outro array com M valores distintos (values_search).
O Pai deve criar M filhos, cada um dos M filhos deve procurar um dos M valores presentes no array "values_search"; 
O filho deve returnar ao pai via pipe, o seu pid, o valor e o index correspondente Ã  posiÃ§Ã£o do valor do array "input".  

"PID:pid; Value: value; Index: index\n|"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define M 20
#define BUF_SIZE 4096

void printArray(int *a, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int binarySearch(int a[], int n, int key) {

    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (key < a[mid]) hi = mid - 1;
        else if (key > a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

int uniform(int val_min, int val_max) {
    return val_min + rand() % (val_max - val_min + 1);
}

char *newCharArray(int N) {
    return (char *) malloc(sizeof(char) * N);
}

void freeCharArray(char *v) {
    free(v);
}

int uniformDistinctArray(int *a, int N, int val_min, int val_max) {
    int i, value, range = val_max - val_min + 1;
    char *b = newCharArray(range);
    for (i = 0; i < range; i++)
        b[i] = 0;
    for (i = 0; i < N; i++) {
        do {
            value = uniform(val_min, val_max);

        } while (b[value - val_min] != 0);
        b[value - val_min] = 1;
        a[i] = value;
    }
    freeCharArray(b);
    return 0;
}

int *newIntArray(int N) {
    return (int *) malloc(sizeof(int) * N);
}

void freeIntArray(int *v) {
    free(v);
}

int compareIntValues(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}

void sortIntArray(int *v, int n) {
    qsort(v, n, sizeof(int), compareIntValues);
}

int main(int argc, char *argv[])
{ 

    int pids[M], fds[2];
    int *input, N = 100000;
    int *values_search;
    
    //alocacao de um array de interiros com N posicoes
    
    input = newIntArray(N);
    //alocacao de um array de interiros com N posicoes
    values_search = newIntArray(M);

    //insercao de N valores aleatorios de 0 a 2*N no array input
    srand(getpid());
    uniformDistinctArray(input,N,0,2*N);
   

    //ordenacao dos valores inseridos
    sortIntArray(input,N);
    //printArray(input,N);

    //insercao de M valores aleatorios a procurar do array input
    uniformDistinctArray(values_search,M,0,2*N);
    
    printf("Values to search: ");
    printArray(values_search,M);

   /*
    * Create the pipe
    */


    
    if(pipe(fds) < 0 ){
    	perror("pipe");
    	exit(1);
    }

    int i = 0;

    /**
     * Criacao de M filho. Cada filho Ã© responsavel 
     * por procurar um determinado valor no array "input".
     * Se o filho encontrar o valor no array, deve returnar, via pipe, o "valor" e o "index" do array "input" onde o encontrou.
     * */
    for (i = 0; i < M; i++) {

  
        pids[i] = fork();

        if (pids[i] == 0) {

            //fecho do seu descritor do lado de leitura do pipe.
            close(fds[0]);

            //pesquisa
            int index = binarySearch(input, N, values_search[i]);

            //se encontrou envia os dados ao pai.
            if (index != -1) {
                char msg[50];
                sprintf(msg, "PID: %d; Value: %d; Index: %d\n|", getpid(), values_search[i], index);
                write(fds[1], msg, strlen(msg));
            }

            //fecho do seu descritor do lado de escrita do pipe.
            close(fds[1]);
            exit(EXIT_SUCCESS);
        }
    }

    //fecho do seu descritor do lado de escrita do pipe.
    close(fds[1]); 

    char buf[BUF_SIZE];
    ssize_t bytes;

    //lÃª dos dados enviados pelos filhos via pipe
    //...
    while((bytes = read(fds[0],buf,BUF_SIZE))!=0){
    	char *message = strtok(buf,"|");
    	while(message != NULL){
    		write(1,message, strlen(message));
    		message = strtok(NULL,"|");
    	}
    }


    int pid = -1;
    int status;
    for(i=0; i < M; i++){
        
        pid = waitpid(pids[i], &status, 0);

        if (WIFEXITED(status)) {
            /*
            WEXITSTATUS(status) - returns the exit status of the child.
            */
            //printf("PID %d Status: %d\n", pid, WEXITSTATUS(status));
        }
    }

    freeIntArray(input);
    freeIntArray(values_search);

    exit(EXIT_SUCCESS);
}
