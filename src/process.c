#include "clibfuncs.h"
#include "elf.h"
#include "page.h"
#include "fat.h"
#include "list.h"
#include "mmu.h"
#include "rprintf.h"
#include "nalloc.h"
#include "serial.h"
#include "process.h"

struct process *currProcess;
struct 

//exec
// 1 - copy elf file into memory
// 2 jump to the correct address to run

int _exec(char *path, char *argv[]){	
	struct file fd;
	unsigned int filesize;
	int k;
	void *temp_vaddr = (void*)0x200000;
	struct physical_page *temp_space;
	struct physical_page *junk_space;
	struct physical_page *
	struct Elf64_Ehdr *hdr; //file header
	struct Elf64_Phdr *pr_hdr; //program header
	struct process *newProcess = nalloc(sizeof(struct process));
	int argc = 1; //character count of argv. starts at 1 because argc will be 1 + number of spaces between arguments

// add check to verify that argv is not NULL. Count number of arguments in argv
	if(argv == NULL){
		// return error or esp_printf(putc, "No arguments");  ??
	}
	int i = 0;
	while(argv[i] != NULL){
		if(argv[i] = ' ') //looking for open spaces in arg v
			argc++;	
	}
	
	if(newProcess == NULL){
		return -1;
	}

	if(fatOpen(path, &fd) < 0){
		return -1;
	}

	junk_space = allocate_physical_pages(1);	
	mapPages(temp_vaddr,junk_space->physical_addr);

	memset(newProcess, 0,sizeof(struct process)); // zero out memory in newProcess

	strcpy(newProcess->path, path); //copy path if included in struct

//create addProcess to add process to list of active processes; just use ListAdd() and create a dummy list of process


	currProcess = newProcess;
	filesize = fd->rde->file_size / PAGE_SIZE + 1; 
	fatRead(&fd, (void*)temp_vaddr, filesize);


//put contents into physical page & map physical pages to vaddr space
	//temp buffer for headers
	hdr = temp_vaddr;
	pr_hdr = temp_vaddr + hdr->e_phoff;	

	for (int i = 0; i < hdr->e_phnum; i++) { //loop through program hdr entries

		
		void *vaddr = (void*) pr_hdr[i].p_vaddr;
		struct ppage* page_alloc = 0;

		
		temp_space = allocate_physical_pages(1); 
		temp_vaddr = mapPages(vaddr, page_alloc->physical_addr);   

		if (pr_hdr[i].p_type == PT_LOAD){     //added check to see if program is loadable
		memcpy(vaddr,temp_vaddr + pr_hdr[i].p_offset, pr_hdr[i].p_filesz);
		}

		if(temp_vaddr < 0) {
			return -1;
		}

		 //read contents of elf file into memory
		vaddr += PAGE_SIZE;
			

	}


	//set hdr = temp_vaddr
	//use the program header offset to find where it starts temp_vaddr+hdr->phoff

//create a new segement for each loadable  header;
//link that segment to the linked list of segments within our process struct
//copy the data from our elf file image into the vaddr where the process is going to live in memory

}