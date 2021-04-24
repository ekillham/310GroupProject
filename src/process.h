#ifndef _PROCESS_H
#define _PROCESS_H

struct process {
	struct process *next;
	struct process *prev;
	uint64_t pid; /* Process ID */
	struct segment *segmentList;
    char *path;
};

struct segement {
	struct segment *next;
	struct segment *prev;
	void *vaddr; /* Base of Segement */
	struct physical_page *ppage_list; /* list of pages eassociated with segement might not be necessary */
	struct page_directory_entry *pd; /* Process page directory and associated page table */
};

#endif
