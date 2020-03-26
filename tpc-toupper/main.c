#include "library.h"


int main(int argc, char* argv[])
{
	int i;
	char c;
	int fds_1[2];
	pipe(fds_1);
        create_pipe_2_global();
        pid_t pid;

   	pid = fork();
   	if (pid == 0){
   	
      close(fds_1[1]);
		
		while((i=read(fds_1[0],&c,1))!=0){
			c = toupper(c);
			write(fds_2[1],&c,1);
		}
    		int ppid = getppid();

    		kill(ppid, SIGUSR1);

			close(fds_1[0]);
			close(fds_2[1]);
			exit(EXIT_SUCCESS);
	}else{
   		signal(SIGUSR1, handler);
		close(fds_1[0]);
		close(fds_2[1]);
		while((i=read(0,&c,1))!=0) write(fds_1[1],&c,1);
		close(fds_1[1]);

		wait(NULL);
    }

}

void handler(){
	int i;
	char c;
	while((i=read(fds_2[0],&c,1))!=0)
			write(1,&c,1);
	close(fds_2[0]);
}
