#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "image.h"
#include "block.h"

int find_low_clear_bit(unsigned char x)
{
    for (int i = 0; i < 8; i++)
        if (!(x & (1 << i)))
            return i;
    
    return -1;
}

void set_free(unsigned char *block, int num, int set){
	int byte = num / 8;  
	int bit = num % 8;
	unsigned int bit_pos = 1 << bit;
	if (set == 1){
    	block[byte] = block[byte] | bit_pos;
    }else{
    	bit_pos = ~bit_pos;
    	block[byte] = block[byte] & bit_pos;
    }
}

int find_free(unsigned char *block){
	for (int i = 0; i < 4096; i++){
        int low_bit = find_low_clear_bit(block[i]);
    	if (low_bit > -1){
    		return ((i * 8) + low_bit);
    	}
    }
	return -1;
}