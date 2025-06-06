#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "image.h"
#include "block.h"
#include "free.h"

int ialloc(void){
	unsigned char inodeblock[4096];
	bread(1,inodeblock);
	int free_node = find_free(inodeblock);
	set_free(inodeblock, free_node, 1);
	bwrite(1, inodeblock);
	return free_node;
}