#include "rprintf.h"
#include "elf.h"

int parse_elf_header(void *start) {
	int k;
	struct Elf64_Ehdr *hdr = start;
	struct Elf64_Phdr *phdr = start+hdr->e_phoff;

		printk("Magic number   = %08x\n", hdr->e_ident[EI_MAG0] && hdr->e_ident[EI_MAG1] && hdr->e_ident[EI_MAG2] && hdr->e_ident[EI_MAG3]);
    	printk("ELF Class      = %02x (%s)\n", hdr->e_ident[EI_CLASS], hdr->e_ident[EI_CLASS] == 1 ? "32 Bit" : "64 Bit");
   		printk("Endianness     = %02x (%s)\n", hdr->e_ident[EI_DATA, hdr->e_ident[EI_DATA] == 1 ? "Little" : "Big");
    	printk("ELF Version    = %02x\n", hdr->e_ident[EI_VERSION);
    	printk("OS ABI         = %02x\n", hdr->e_ident[EI_OSABI]);
    	printk("OS ABI Version = %02x\n", hdr->e_ident[EI_ABIVERSION]);
    	printk("Obj File Type  = %04x\n", hdr->e_type);
    	printk("Architecture   = %04x\n", hdr->e_machine);
    	printk("Version        = %08x\n", hdr->e_version);
    	printk("Entry Point    = %08x\n", hdr->e_entry);

    	for(k = 0; k < hdr->e_phnum; k++) {
        	printk("\n--- Program Header %d ---\n", k);
        	printk("Segment type = %08x\n", phdr->p_type);
       		printk("Offset       = %08x\n", phdr->p_offset);
        	printk("Virt Addr    = %08x\n", phdr->p_vaddr);
        	printk("Phys Addr    = %08x\n", phdr->p_addr);
        	printk("Size in file = %08x\n", phdr->p_filesz);
        	printk("Size in mem  = %08x\n", phdr->p_memsz);
        	printk("Flags        = %08x\n", phdr->p_flags);
        	printk("Alignment    = %08x\n", phdr->p_align);
        	phdr++;
    	}

}

int is_elf(Elf64_Ehdr *hdr){
	
	int iself = -1
	// breaking out  tests into individual checks
	if (
    		hdr->e_ident[EI_MAG0] == 0x7f &&
    		hdr->e_ident[EI_MAG1] == 'E' &&
    		hdr->e_ident[EI_MAG2] == 'L' &&
    		hdr->e_ident[EI_MAG3] == 'F'
    	) {
        	iself = 0; 
    	}

    	if (iself != -1){
    		iself = hdr->type;
    	}

    	return iself;
	
}