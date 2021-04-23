#include "clibfuncs.h"
#include "elf.h"
#include "page.h"
#include "fat.h"
#include "list.h"
#include "mmu.h"
#include "rprintf.h"
#include "nalloc.h"
#include "serial.h"


/*adding notes to this file from our initial meeting w/ Neil so that everyone can continue to writing to it while understanding the different steps we need to exec to go through */

//exec
// 1 - copy elf file into memory
// 2 jump to the correct address to run

int _exec(char *path, struct process_context *ctx char *argv[]){	
	struct file fd;
	int filesize;
	int k;
	void *temp_vaddr = (void*)0x200000;
	struct physical_page *temp_space;
	struct Elf64_Ehdr *hdr;
	struct Elf64_Phdr *pr_hdr;
	struct process *newProcess = nalloc(sizeof(struct process));
	int argc;

// add check to verify that argv is not NULL. Count number of arguments in argv

	if(newProcess == NULL){
		return -2;
	}

	if(fatOpen(path &fd) < 0){
		return -1;
	}

//get filesize of so that we can size the pages correctly - getfilesize function  

	memset(newProcess, 0,(struct process)); // zero out memory in newProcess

	strcpy(newProcess->path, path) //copy path if included in struct .. might remove later

//create addProcess to add process to list of active processes; just use ListAdd() and create a dummy list of process
//discuss with group how much we want to go into process handling and lists.

	currProcess = newProcess;

//put contents into physical page & map physical pages to vaddr space

//read contents of elf file into memory
	//set hdr = temp_vaddr
	//use the program header offset to find where it starts temp_vaddr+hdr->phoff

//loop through program headers; create a new segement for each loadable  header; link that segment to the linked list of segments within our process struct
//setup vaddr; map that new segement into the page table for the process
//copy the data from our elf file image into the vaddr where the process is going to live in memory