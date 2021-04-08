#include <stdio.h>
#include "clibfuncs.h"
#include "nalloc.h"
#include "rprintf.h"

void runShell (int argc, char **argv){
	char *line, *argz;
	//pid_t pid, wpid;
	unsigned int bufsize = 0;

	while(1){

		esp_printf(putc,"> ");
		getline(&line, &bufsize, stdin);

		pid = fork();

		if(pid == 0) {
		argz = nalloc(2*sizeof(char*));
		argz =  {line, NULL};

		execv(line,argz);

		}

		nfree(line);
		nfree(argz);

	}

}

