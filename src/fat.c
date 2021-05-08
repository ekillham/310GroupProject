#include "fat.h"
#include "sd.h"
#include "rprintf.h"
#include "serial.h"
#include "clibfuncs.h"
#include "uart.h"

struct boot_sector *bs;
char bootSector[512];
char fat_table[8*SECTOR_SIZE];
struct root_directory_entry *fat_sector_read;
char rootSector[512];

unsigned int root_sector;
unsigned int first_data_sector;

int fatInit() {
	char buffer[8*SECTOR_SIZE];
	sd_readblock(0, (unsigned char*) bootSector, 1);
	bs = (struct boot_sector*) bootSector;
	int k=0;

	int ret = 1;
	while  (bs->fs_type[k] != ' '|| k >= 8){
		buffer[k] = bs->fs_type[k];
		k++;
		buffer[k] = 0;

	}
	
	if (bs->boot_signature == 0xaa55){
		ret = 0;
		return ret;
	}

	if (strcmp(buffer, "FAT16")){
		ret = 0;
		return ret;
	}

	root_sector = ((bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors);

	first_data_sector = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat) + ((bs->num_root_dir_entries * 32) + (SECTOR_SIZE - 1)) / SECTOR_SIZE;

	return 0;
}

//struct file *file_open;

int fatOpen(struct file* readfile, char* filename){
	int t_sectors = bs->num_root_dir_entries;
	int t = 1;
	char buffer[10];
	unsigned int sector = root_sector;
	
	sd_readblock(sector, (unsigned char*) buffer, 8);
	fat_sector_read = (struct root_directory_entry*) buffer;
	while (t < t_sectors){
		int k = 0;
		while (k < 8){
			if (fat_sector_read->file_name[k] != ' ')
				buffer[k] = fat_sector_read->file_name[k];
			k++;
		}
		buffer[7] = 0;
		
		if (strcmp(buffer, filename) == 0){
			
			readfile->rde = *fat_sector_read;
			readfile->start_cluster = fat_sector_read->cluster;
			return 0;
		}
		
		t++;
		fat_sector_read++;
	}
	return -1;
}

//TODO: Rewrite / add functionality to handle multiple clusters. Need to know where each cluster starts and how big a cluster is 
//      find next cluster in the fat table 
void fatRead(struct file* readfile,char *buffer,int bytes_read){
	
	int file_size = readfile->rde.file_size;
	int offset = readfile->rde.cluster * 2; // from OSDev need to verify if this will work

	int cluster = readfile->start_cluster + offset / (bs->num_sectors_per_cluster * bs->bytes_per_sector);
	int sector = ((cluster - 2) * bs->num_sectors_per_cluster) + first_data_sector;

	int end_file = bytes_read + offset ;

	while (file_size < end_file) {
		
		sd_readblock(sector, (unsigned char*) buffer, bs->num_sectors_per_cluster); //read active cluster

		buffer += bs->num_sectors_per_cluster;
		// need a loop to get size of cluster, how many bytes need to be processed

	
		cluster = fat_table[cluster];
		sector = ((cluster - 2) * bs->num_sectors_per_cluster) + first_data_sector;

		
		if (cluster >= 0xfff7){
			break;
		}
		
	}

}

