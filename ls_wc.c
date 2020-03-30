#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


void handler (int signal_number)
{
    switch(signal_number){
        case SIGUSR1:
            //printf ("Received a SIGUSR1...\n");
            break;
        case SIGUSR2:
            //printf ("Received a SIGUSR2...\n");
            break;
        case SIGCHLD:
            printf ("Received a SIGCHLD...\n");
            break;
        default:
            printf ("Received a %d signal...\n",signal_number);
            break;
    }
}

/**
 * ls -a -l | wc -l 
 * 
 *  fork1 ('ls -a -l')
 *              |            __________
 *              ->    fds[1] ---------- fds[0] 
 *                                          |                               ******
 *                                           ->  fork2('wc -l')  -  Output: * $     25
 *                                                                          * Received a SIGCHLD...
 *                                                                          * Received a SIGCHLD...
 *                                                                          * PID 83859 Status: 0
 *                                                                          * PID 83860 Status: 0
 *                                                                          * DONE!
 */                                                         
int main(int argc, char *argv[])
{
    int pid1, pid2;
    int fds[2]; 

    //#1 Signal installation handler

    struct sigaction sa;

    memset(&sa, 0, sizeof(sa)); //memset - fill memory with a constant byte

    /*
       sa_handler specifies the action to be associated with signum and may
       be SIG_DFL for the default action, SIG_IGN to ignore this signal, or
       a pointer to a signal handling function.  This function receives the
       signal number as its only argument.
    */

    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART;
    //... 

   
    /* The sigaction() system call is used to change the action taken by a
       process on receipt of a specific signal. */
    
    sigaction(SIGCHLD,&sa,NULL);



    //#2 Pipe
    /* 
    Create a pipe.  File descriptors for the two ends of the pipe are
    placed in fds.  
    
    int pipe(int fds[2]);

    Parameters : fds[0] will be the fd(file descriptor) for the read end of pipe.
                 fds[1] will be the fd for the write end of pipe.
    Returns : 0 on Success. -1 on error.
    */

   /*
    * Create the pipe
    */

    if(pipe(fds) == -1){

        perror("pipe");
        exit(EXIT_FAILURE);

    }
   
    //#2 -- Pipe

    /* fork() - create a child process.
        
       fork() creates a new process by duplicating the calling process.  The
       new process is referred to as the child process.  The calling process
       is referred to as the parent process.
    */

    if((pid1 = fork()) <0){

        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0)
    {
        //FILHO 1 ("ls -a -l")

        /* Close our copy of the read end of the file descriptor. */ 
        //close(fds[0]);   
        //close(1);
		//dup(fds[1]);
        /* Connect the write end of the pipe to standard output.  */
        dup2(fds[1],STDOUT_FILENO);

        /*
        The exec family of functions shall replace the current process image with a new process image. 
        The new image shall be constructed from a regular, executable file called the new process 
        image file. 
        There shall be no return from a successful exec, because the calling process image is overlaid 
        by the new process image.
        */

        execlp("ls","ls","-a","-l",NULL);

        perror("fork");
        exit(EXIT_FAILURE);
        }
    else
    {
        //PAI
        //FILHO 2 ("wc -l")

        if((pid2 = fork ()) < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0)
        {
            
            close(fds[1]);/* Close our copy of the write end of the file descriptor. */

            //close(0);
		    //dup(fds[0]);
            /* Connect the read end of the pipe to standard input.  */
            dup2(fds[0],STDIN_FILENO);

            execlp("wc","ls","-l","-a",NULL);

            perror("exec failled");
            exit(EXIT_FAILURE);
        }

        //PAI
        close(fds[0]); /* Close unused read end */
        close(fds[1]); /* Close unused write end */
        
        int status;
        /*
        The waitpid() system call suspends execution of the calling process 
        until a child specified by pid argument has changed state.
        */

        pid1 = waitpid(pid1,&status,0);

        /**
         * WIFEXITED(status) - returns true if the child terminated normally.
         */ 
        if (WIFEXITED(status)) {
            /*
            WEXITSTATUS(status) - returns the exit status of the child.
            */
            printf("PID %d Status: %d\n", pid1, WEXITSTATUS(status));
        }

        pid2 = waitpid(pid2,&status,0);


        if (WIFEXITED(status)) {
            printf("PID %d Status: %d\n", pid2, WEXITSTATUS(status));
        }
        printf("DONE!\n");

        /* The exit() function causes normal process termination and the value
            of status is returned to the parent.
        */
        exit(EXIT_SUCCESS);
    }
}

