#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "image.h"
#include "block.h"
#include "free.h"
#include "pack.h"
#include "inode.h"
static struct inode incore[MAX_SYS_OPEN_FILES] = {0};

int ialloc(void){
	unsigned char inodeblock[4096];
	bread(1,inodeblock);
	int free_node = find_free(inodeblock);
	set_free(inodeblock, free_node, 1);
	bwrite(1, inodeblock);
	return free_node;
}

struct inode *incore_find_free(void){
	int size = sizeof(incore) / sizeof(incore[0]);
	for (int i = 0; i < size; i++) {
        if (incore[i].ref_count == 0){
        	return &incore[i];
        }
    }
    return NULL;
}

struct inode *incore_find(unsigned int inode_num){
	int size = sizeof(incore) / sizeof(incore[0]);
	for (int i = 0; i < size; i++) {
        if (incore[i].ref_count != 0 && incore[i].inode_num == inode_num){
        	return &incore[i];
        }
    }
	return NULL;
}

void incore_free_all(void){
	int size = sizeof(incore) / sizeof(incore[0]);
	for (int i = 0; i < size; i++) {
        incore[i].ref_count = 0;
    }
}

void read_inode(struct inode *in, int inode_num){
	unsigned char inodeblock[4096];
	int block_num = inode_num / INODES_PER_BLOCK + INODE_FIRST_BLOCK;
	int block_offset = inode_num % INODES_PER_BLOCK;
	int block_offset_bytes = block_offset * INODE_SIZE;

	bread(block_num, inodeblock);
	unsigned int v = read_u32(inodeblock + block_offset_bytes);
	in->inode_num = v;
	(void)in;
	(void)inode_num;
}

void write_inode(struct inode *in){
	(void)in;
}

struct inode *iget(int inode_num){
	(void)inode_num;
	return NULL;
}

void iput(struct inode *in){
	(void)in;
}