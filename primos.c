
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
	pid_t pid[2];
    	int primes[]={2,3,5,7,11,13,17,19,23,29};

	for(int i = 0; i <2; i++){
		/* processso filho */
		if((pid[i]= fork())==0){
			if(i == 0){ // se estiver no primeiro processo que soma os pares
			int sumpares = 0; // contem a soma dos valores pares
				for(int j = 0; j < 10; j++){ // itera o array
				
					if(j%2==0){ // testa se esta numa posicao par
            					sumpares+=primes[j];
            					primes[j]=0;
        				}
				}
			exit(sumpares);// termina o processo da soma de pares
			}
			if(i == 1){ // se estiver no segundo processo que soma os impares
			int sumimpares = 0; // contem a soma dos valores impares
				for(int j = 0; j < 10; j++){ // itera o array
				
					if(j%2!=0){ // testa se esta numa posicao impar
            					sumimpares+=primes[j];
            					primes[j]=0;
        				}
				}
			exit(sumimpares); // termina o processo da soma de impares
			}

		}else{
		/* processo pai */ 

			 int result;
   			 wait(&result);
			if(i==0){
    			 printf("Child1 pid: %d \t valor da soma dos pares: %d\n",pid[i],WEXITSTATUS(result));
			}
			if(i==1){
			printf("Child2 pid: %d \t valor da soma dos impares: %d\n",pid[i],WEXITSTATUS(result));
			}
		}
			
	}

   
    return 0;
}
