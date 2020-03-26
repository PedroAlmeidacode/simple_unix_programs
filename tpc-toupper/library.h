#ifndef LIBRARY_H
#define LIBRARY_H


#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>
#include <unistd.h>


extern int fds_2[2];

void create_pipe_2_global(void);
void handler();

#endif
