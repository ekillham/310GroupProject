#include <stdio.h>
#include "clibfuncs.h"
#include "nalloc.h"
#include "rprintf.h"
#include "uart.h"




void main (int argc, char **argv){
	char *line, **argz;
	//pid_t pid, wpid;
	unsigned int bufsize = 0;
    int pid;

    esp_printf(uart_send, "Hello from the shell!!!");    

#if 0
	while(1){

		esp_printf(putc,"> ");
		getline(&line, &bufsize, stdin);

//		pid = fork();

		if(pid == 0) {
		argz = nalloc(2*sizeof(char*));
		//argz =  {line, NULL}; // NAK this didn't compile, so I manually set argz[0] and argz[1]
        argz[0] = line;
        argz[1] = NULL;

		exec(line,argz);

		}

		nfree(line);
		nfree(argz);

	}
#endif

}

