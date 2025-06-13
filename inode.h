#ifndef INODE_H
#define INODE_H
#define INODE_PTR_COUNT 16
#define MAX_SYS_OPEN_FILES 64
#define BLOCK_SIZE 4096
#define INODE_SIZE 64
#define INODE_FIRST_BLOCK 3

#define INODES_PER_BLOCK (BLOCK_SIZE / INODE_SIZE)

struct inode {
    unsigned int size;
    unsigned short owner_id;
    unsigned char permissions;
    unsigned char flags;
    unsigned char link_count;
    unsigned short block_ptr[INODE_PTR_COUNT];

    unsigned int ref_count;  // in-core only
    unsigned int inode_num;  // in-core only
};

int ialloc(void);

struct inode *incore_find_free(void);

struct inode *incore_find(unsigned int inode_num);

void incore_free_all(void);

void read_inode(struct inode *in, int inode_num);

void write_inode(struct inode *in);

struct inode *iget(int inode_num);

void iput(struct inode *in);

#endif