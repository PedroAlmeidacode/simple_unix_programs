#include "library.h"


int fds_2[2];

void create_pipe_2_global(void)
   {
   pipe(fds_2);
   }
