#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>

int main(int argc,char **argv)
{
	char c;
	int pipe1[2],pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	int i;
	
	
	pid_t pid=fork();
	if (pid==0)
	{
		printf("Filho\n");
		close(pipe1[1]);
		
		close(pipe2[0]);

		while(( i= read(pipe1[0],&c,1)) != 0){
			c = toupper(c);
			write(pipe2[1],&c,1);

		}
		
		close(pipe2[1]);
		close(pipe1[0]);

		exit(0);
		
	}

	
		close(pipe1[0]);
		close(pipe2[1]);
		printf("Pai\n");

		while((i = read(0,&c,1))!= 0){
			write(pipe1[1],&c,1);
		}
		
		close(pipe1[1]);
		write(1,"\n",1);	
		while((i = read(pipe2[2],&c,1))!= 0){
			write(1,&c,1);
		}

		write(1,"\n",1);
		exit(EXIT_SUCCESS);

	
	return 0;
}
