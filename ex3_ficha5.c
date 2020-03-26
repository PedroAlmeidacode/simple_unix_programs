
#include "/home/pedro/Desktop/apue.h"
#define BUFFSIZE 4096

int main(int argc,char **argv)
{

	int i,n;
	int pids[2];
	int pipefd[2];
	if(pipe(pipefd)== -1){
		perror("pipe");
		exit(1);
	}
	

	for(i=0; i <2; i++){

		if((pids[i] = fork()) == -1){
			perror("fork");exit(-1);}


		if(pids[i] == 0){
			int fd;
			char *token ;
			char buf[BUFFSIZE];

			close(pipefd[0]);

			fd = open("file.txt",O_CREAT | O_RDWR, 0644);



			while((n = read(fd, buf, BUFFSIZE)) != 0){
				token = strtok(buf,"\n");
				while(token != NULL){
					char msg[200];
					sprintf(msg,"%d*%s#\n",getpid(),token);

					write(pipefd[1],msg,strlen(msg));
					token = strtok(NULL, "\n");
		
				}


			}

			close(pipefd[1]);
			exit(EXIT_SUCCESS);
		}


	}





	close(pipefd[1]);
	char buffer[BUFFSIZE];


	while(n = read(pipefd[0],buffer,BUFFSIZE))
		// escrever para stout
		write(1, buffer,n);
		

	for(i =0; i < 2; i++){
		//esperar pelos filhos 
		waitpid(pids[i],NULL,0);

	}







}























