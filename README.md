# File System

## Building

Command line:

* `make` to build. An executable called `testfs` will be produced.
* 'make test' to build and run the executable immediately.
* `make clean` to clean up all build products except the executable and the static library.
* `make pristine` to clean up all build products entirely.


## Files

* `testfs.c`: The main code for testing the file system
* `image.c`: Code that describes functions for the file system image
* `block.c`: Code that describes functions for the data blocks
* `free.c`: Code that describes functions for setting data as free or not free, and finding free spots in memory
* `inode.c`: Code that describes functions for inode blocks
* `pack.c`: Helper functions for packing and unpacking


## Data

Image files can be opened and are used to store blocks of data. Unsigned char arrays are used as buffers for the data.


## Functions

testfs - 
* 'main()': (referring to the main inside the ctest if block, the other main() is unused) Runs the ctest tests to test the file system
  * 'test_image()': Tests to make sure image functions work
  * 'test_block()': Tests to make sure block functions work
  * 'test_free()': Tests to make sure free functions work
  * 'test_alloc()': Tests to make sure allocation functions work
  * 'test_inode()': Tests to make sure inode functions work

image.c - 
* 'image_open': Opens an image file with a specified name, optionally truncated
* 'image_close': Closes the most recently opened image file

block.c - 
* 'bread()': Reads from a block at a specified block number and returns the data
* 'bwrite()': Writes data to a block at a specified block number
* 'alloc()': Finds a free data block and allocates it

inode.c -
* 'ialloc()': Finds a free inode block and allocates it
* 'incore_find_free()': Finds the first free incore inode
* 'incore_find()': Finds an incore inode wit the specified inode number
* 'incore_free_all()': Frees all incore inodes by setting their ref_count to 0

free.c -
* 'set_free()': Sets a specific bit in a block to either be 0 or 1, meaning free or not free
	* 'find_free()': Finds the lowest 0 bit in a byte
* 'find_free()': Finds the first free bit in a block and returns its index


## Notes

* None