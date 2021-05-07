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

int global;
#define NULL (void*)0
extern long __bss_start;
extern long __bss_end;
extern struct ppage* free_list;

unsigned int *gpset1 = 0xFE200020;
unsigned int *gpclr1 = 0xFE20002C;
unsigned int *gpsel4 = 0xFE200010;

//HW1 Office Hours 2/1 w/ Jack
void clear_bss()

{
	int x = 0;
	while ((&__bss_start)+x != &__bss_end){
		(&__bss_start)[x] = 0;
		x++;
		}
}

int getEL(){
	unsigned int el;

	asm("mrs %0,CurrentEL"
		: "=r"(el)
		:
		:);

}


void kernel_main(){
	clear_bss();

	struct file fat_test;

	init_pfa_list();
	sd_init();
	fatInit();

	_exec("shell");

	while(1){

	}
}



