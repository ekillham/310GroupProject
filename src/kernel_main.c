#include "list.h"
#include "serial.h"
#include "rprintf.h"
#include "page.h"
#include "mmu.h"
#include "fat.h"
#include "sd.h"
#include "clibfuncs.h"
#include "uart.h"
#include "elf.h"
#include "nalloc.h"
#include "process.h"

int global;
extern long __bss_start;
extern long __bss_end;
extern struct ppage* free_list;

void clear_bss()

{
	int x = 0;
	while ((&__bss_start)+x != &__bss_end){
		(&__bss_start)[x] = 0;
		x++;
		}
}


void kernel_main(){
	clear_bss();

	uart_init();
	memInit();

	init_pfa_list();
	sd_init();
	fatInit();

	_exec("shell",0);

	while(1){

	}
}



