#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "image.h"
#include "free.h"

unsigned char *bread(int block_num, unsigned char *block){
	off_t offset = lseek(image_fd, 4096 * block_num, SEEK_SET);
	read(image_fd, block, 4096);
	return block;
	(void) offset;
}

void bwrite(int block_num, unsigned char *block){
	off_t offset = lseek(image_fd, 4096 * block_num, SEEK_SET);
	write(image_fd, block, 4096);
	(void) offset;
}

int alloc(void){
	unsigned char datablock[4096];
	bread(2,datablock);
	int free_node = find_free(datablock);
	set_free(datablock, free_node, 1);
	bwrite(2, datablock);
	return free_node;
}