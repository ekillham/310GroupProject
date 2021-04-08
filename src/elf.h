
#include "terminal.h"
#include "rprintf.h"
#include "elf.h"



int parse_elf_header(void *start) {
    int k;
    struct elf32_header *hdr = start;
    struct elf_program_header *prog_hdr = start+hdr->e_phoff;

    printk("Magic number   = %08x\n", hdr->magic);
    printk("ELF Class      = %02x (%s)\n", hdr->elfclass, hdr->elfclass == 1 ? "32 Bit" : "64 Bit");
    printk("Endianness     = %02x (%s)\n", hdr->endianness, hdr->endianness == 1 ? "Little" : "Big");
    printk("ELF Version    = %02x\n", hdr->elfversion);
    printk("OS ABI         = %02x\n", hdr->osabi);
    printk("OS ABI Version = %02x\n", hdr->osabiversion);
    printk("Obj File Type  = %04x\n", hdr->e_type);
    printk("Architecture   = %04x\n", hdr->e_machine);
    printk("Version        = %08x\n", hdr->e_version);
    printk("Entry Point    = %08x\n", hdr->e_entry);

    // Look thru the program header...
    for(k = 0; k < hdr->e_phnum; k++) {
        printk("\n--- Program Header %d ---\n", k);
        printk("Segment type = %08x\n", prog_hdr->type);
        printk("Offset       = %08x\n", prog_hdr->offset);
        printk("Virt Addr    = %08x\n", prog_hdr->vaddr);
        printk("Phys Addr    = %08x\n", prog_hdr->paddr);
        printk("Size in file = %08x\n", prog_hdr->filesz);
        printk("Size in mem  = %08x\n", prog_hdr->memsz);
        printk("Flags        = %08x\n", prog_hdr->flags);
        printk("Alignment    = %08x\n", prog_hdr->align);
        prog_hdr++;
    }

    if(hdr->magic != 0x464c457f) { // Check for valid magic number in ELF header
        return -1;
    }
    if(hdr->e_machine != 3) { // Check for correct machine type (3 indicates x86)
        return -2;
    }

    return 0;
}
