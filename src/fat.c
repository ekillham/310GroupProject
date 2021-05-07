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
	char buffer[10];
	sd_readblock(0, bootSector, 1);
	bs = bootSector;
	int k=0;
	while  (bs->fs_type[k] != ' '|| k >= 8){
		esp_printf(putc, "%c", bs->fs_type[k]);
		buffer[k] = bs->fs_type[k];
		k++;
		buffer[k] = 0;

	}
	/* TODO #1 */
	if (bs->boot_signature == 0xaa55){
		esp_printf(putc, "Validated boot signature \n");
	}

	if (strcmp(buffer, "FAT16")){
		esp_printf(putc, "It is FAT16 \n");
	}
/*
	esp_printf(putc,"Bytes per sector--> %d \n" ,bs->bytes_per_sector);
	esp_printf(putc,"Sectors per cluster--> %d \n" ,bs->num_sectors_per_cluster);
	esp_printf(putc,"Reserved sectors--> %d \n" ,bs->num_reserved_sectors);
	esp_printf(putc,"Fat Table--> %d \n" ,bs->num_fat_tables);
	esp_printf(putc,"Root Directory entries--> %d \n" ,bs->num_root_dir_entries); 
*/
	int root_sector_value = ((bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors);
//	esp_printf(putc,"Root Sector value --> %d \n", root_sector_value);

	first_data_sector = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat) + ((bs->num_root_dir_entries * 32) + (SECTOR_SIZE - 1)) / SECTOR_SIZE;
}

struct file *file_open;

int fatOpen(struct file* readfile, char* filename){
	int t_sectors = bs->num_root_dir_entries;
	int t = 1;
	char buffer[10];
	int root_sector_value = ((bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors);
	esp_printf(putc, "BOOT SECTOR = %x\n", bs);
	sd_readblock(root_sector_value, rootSector, 1);
	fat_sector_read = rootSector;
	while (t < t_sectors){
		int k = 0;
		while (k < 8){
			esp_printf(putc, "%c", fat_sector_read->file_name[k]);
			if (fat_sector_read->file_name[k] != ' ')
				buffer[k] = fat_sector_read->file_name[k];
			k++;
		}
		buffer[7] = 0;
		/* TODO #2 */
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
	
	//int root_sector_value = ((bs->num_fat_tables * bs->num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors);
	//int first_root_dir = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat) + ((bs->num_root_dir_entries * 32) + (bs->bytes_per_sector - 1)) / bs->bytes_per_sector;
	//int first_sector = first_root_dir + ((readfile->rde.cluster - 2) * bs->num_sectors_per_cluster);

	//char cl_buffer[8*SECTOR_SIZE];
	
	int file_size = readfile->rde.file_size;
	int offset = readfile->rde.cluster * 2; // from OSDev need to verify if this will work

	
	//int bytes_per_cluster = bs->num_sectors_per_cluster*bs->bytes_per_sector;

	int cluster = readfile->start_cluster + offset / (bs->num_sectors_per_cluster * bs->bytes_per_sector);
	int sector = ((cluster - 2) * bs->num_sectors_per_cluster) + first_data_sector;

	int end_file = bytes_read + offset ;

	while (file_size < end_file) {
		
		sd_readblock(sector,buffer,bs->num_sectors_per_cluster); //read active cluster

		buffer += bs->num_sectors_per_cluster;
		// need a loop to get size of cluster, how many bytes need to be processed

	
		cluster = fat_table[cluster];
		sector = ((cluster - 2) * bs->num_sectors_per_cluster) + first_data_sector;

		
		if (cluster >= 0xfff7){
			break;
		}
		
	}

}

