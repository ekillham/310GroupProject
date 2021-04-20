#ifndef _ELF_H
#define _ELF_H

#include <stdint.h>

//Segement Types ref:https://www.uclibc.org/docs/elf-64-gen.pdf
#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_LOOS 0x60000000
#define PT_HIOS 0x6FFFFFFF
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7FFFFFFF

/* Segement Attributes */

#define PF_X   0x1  /* execute perm */
#define PF_W   0x2  /* write perm */
#define PF_R   0x3  /* read perm */

/*ELF64 Data Types*/

typedef uint64_t Elf64_Addr; /* unsigned program address - 8 */
typedef uint64_t Elf64_Off; /* unsigned file offset - 8 */
typedef uint16_t Elf64_Half; /* unsigned half int - 2 */
typedef uint32_t Elf64_Word; /* unsigned int - 4 */
typedef uint32_t Elf64_Word; /* unsigned int  - 4 */
typedef int32_t Elf64_Sword; /* signed int  - 4 */
typedef uint64_t Elf64_Xword; /* unsigned long int - 8 */
typedef int64_t Elf64_Sxword; /* signed long int - 8 */

/* File Header */
typedef struct{

	unsigned char e_ident[16]; /* ELF identification */
	Elf64_Half   e_type;       /* Object file type */
	Elf64_Half   e_machine;    /* Machine type */
	Elf64_Word   e_version;    /* Object file version */
	Elf64_Addr   e_entry;      /* Entry point address */
	Elf64_Off    e_phoff;      /* Program header offset */
	Elf64_Off    e_shoff;      /* Section header offset */
	Elf64_Word   e_flags;      /* Processor-specific flags */
	Elf64_Half   e_ehsize;     /* ELF header size */
	Elf64_Half   e_phentsize;  /* Size of program header entry */
	Elf64_Half   e_phnum;      /* Number of program header entries */
	Elf64_Half   e_shentsize;  /* Size of section header entry */
	Elf64_Half   e_shnum;      /* Number of section header entries */
	Elf64_Half   e_shstrndx;   /* Section name string table index */
} Elf64_Ehdr;

/* ELF Identification */

#define EI_MAG0       0 /* File Identification */ 
#define EI_MAG1       1
#define EI_MAG2       2
#define EI_MAG3       3
#define EI_CLASS      4 /* File class */
#define EI_DATA       5 /* Data encoding */
#define EI_VERSION    6 /* File version */
#define EI_OSABI      7 /* OS/ABI identification */
#define EI_AVIBERSION 8 /* ABI Version */
#define EI_PAD        9 /* start of padding bytes */
#define EI_NIDENT    16 /* size of e_ident[] */

/* Object File Classes */
#define ELFCLASS32    1
#define ELFCLASS64    2

/* Data Encodings */
#define ELFDATA2LSB   1
#define ELFDATA2MSB   2

/* Operating System & ABI Identifiers */

#define ELF0SABI_STANDALONE 255 /* for embedded apps */

/* Object File Types */

#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4

/* Section Header entries */

typedef struct{

	Elf64_Word sh_name;       /* Section name */
	Elf64_Word sh_type;       /* Section type */
	Elf64_Xword sh_flags;     /* Section attributes */
	Elf64_Addr sh_addr;       /* Virtual address in memory */
	Elf64_Off sh_offset;      /* Offset in file */
	Elf64_Xword sh_size;      /* Size of section */
	Elf64_Word sh_link;       /* Link to other section */
	Elf64_Word sh_info;       /* Miscellaneous information */
	Elf64_Xword sh_addralign; /* Address alignment boundary */
	Elf64_Xword sh_entsize;   /* Size of entries, if section has table */
} Elf64_Shdr

/* Section Types */

#define SHT_NULL     0    /* unused section header */
#define SHT_PROGBITS 1    /* Program information */
#define SHT_SYMTAB   2    /* linker symbol table */
#define SHT_STRTAB   3    /* string table */
#define SHT_RELA     4    /* Rela type relocation entries */
#define SHT_HASH     5    /* hash table */
#define SHT_DYNAMIC  6    /* dynamic linking tables */
#define SHT_NOTE     7    /* note info */
#define SHT_NOBITS   8    /* uninitialized space */
#define SHT_REL      9    /* Rel type relocation entries */
#define SHT_SHLIB   10    /* reserved */
#define SHT_DYNSYM  11    /* dynamic loader symbol table */

/* Section Attributes */

#define SHF_WRITE     0x1 /* writable data */
#define SHF_ALLOC     0x2 /* allocated in memory image */
#define SHF_EXECINSTR 0x4 /* exe instructions */

/* Program header table */

typedef struct{

	Elf64_Word p_type;    /* Type of segment */
	Elf64_Word p_flags;   /* Segment attributes */
	Elf64_Off p_offset;   /* Offset in file */
	Elf64_Addr p_vaddr;   /* Virtual address in memory */
	Elf64_Addr p_paddr;   /* Reserved */
	Elf64_Xword p_filesz; /* Size of segment in file */
	Elf64_Xword p_memsz;  /* Size of segment in memory */
	Elf64_Xword p_align;  /* Alignment of segment */
} Elf64_Phdr;

int parse_elf_header(void *start)

#endif
