#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "image.h"
#include "block.h"
#include "ctest.h"
#include "free.h"
#include "inode.h"

#ifdef CTEST_ENABLE

void test_image(void)
{
	remove("testfile");
    CTEST_ASSERT(image_open("testfile", 0), "test to make sure opening a file works");
    bool exists = false;
	if (access("testfile", F_OK) == 0) {
	    exists = true;
	}
    CTEST_ASSERT(exists, "test to make sure that after opening a file it exists");
    CTEST_ASSERT(image_close(), "test to make sure closing a file works");
}

void test_block(void){
	image_open("testfile2", 0);
	unsigned char *message = (unsigned char *)"test message";
	unsigned char buffer[4096];
	bwrite(10, message);
	bread(10,buffer);
	CTEST_ASSERT(strcmp((const char *)buffer, (const char *)message) == 0, "writing a message to a block and then reading the block lets you retrieve the message");
}

void test_free(void){
	image_open("testfile3", 0);
	unsigned char inodeblock[4096];
	bread(1,inodeblock); //gets the free inode map
	int free = find_free(inodeblock);
	CTEST_ASSERT(free == 0, "test to make sure find_free works and returns 0 when no blocks have been allocated");

	unsigned char testblock[4096];
	bread(15,testblock);
	set_free(testblock, 50, 1);
}

void test_alloc(void){
	image_open("testfile4", 0);
	int inodeblock1 = ialloc();
	CTEST_ASSERT(inodeblock1 > -1, "test to make sure ialloc works");
	int datablock = alloc();
	CTEST_ASSERT(datablock > -1, "test to make sure alloc works");
	int inodeblock2 = ialloc();
	CTEST_ASSERT(inodeblock2 > inodeblock1, "test to make sure the next block allocated after the first has a higher address number");
}

void test_inode(void){
	struct inode *free_inode = incore_find_free();
	CTEST_ASSERT(free_inode->ref_count == 0, "test to make sure incore_find_free works and returns a pointer to an inode struct");
	free_inode->ref_count = 1;
	free_inode->inode_num = 10;
	struct inode *not_an_inode = incore_find(5);
	CTEST_ASSERT(not_an_inode == NULL, "test to make sure incore_find returns NULL if there is no inode with that inode number");
	struct inode *is_an_inode = incore_find(10);
	CTEST_ASSERT(is_an_inode->inode_num == 10, "test to make sure incore_find is able to find an inode with a specific inode number");
	incore_free_all();
	CTEST_ASSERT(is_an_inode->ref_count == 0, "test to make sure incore_free_all resets the ref count of all inodes to 0");
	struct inode empty;
	read_inode(&empty, 5);
	CTEST_ASSERT(empty.inode_num != 0, "test for read_inode");
}

int main(void)
{
    CTEST_VERBOSE(1);

    test_image();

    test_block();

    test_free();

    test_alloc();

    test_inode();

    CTEST_RESULTS();

    CTEST_EXIT();
}

#else

int main(){
	image_open("filename", 0);
	unsigned char *message = (unsigned char *)"test message";
	unsigned char buffer[4096];
	printf("%s\n", message);
	printf("%li\n", strlen((const char *)buffer));
	bwrite(10, message);
	bread(10, buffer);
	printf("%s\n", buffer);
	printf("%li\n", strlen((const char *)buffer));
	image_close();
}

#endif