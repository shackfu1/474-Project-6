#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

int image_fd;

int image_open(char *filename, int truncate){
	if (truncate){
		image_fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0600);
	}else{
		image_fd = open(filename, O_RDWR|O_CREAT, 0600);
	}
	return 1;
}

int image_close(void){
	close(image_fd);
	return 1;
}
