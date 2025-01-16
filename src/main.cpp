#include <iostream>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 48;
const int NUM_INODES = 16;
const int NUM_FILES = 16;

struct Superblock {
    int magic = 0xf0f03410;
    int num_blocks = NUM_BLOCKS;
    int free_blocks = NUM_BLOCKS;
    int inode_start = 1;
};

struct Inode {
    char name[50];
    int size;
    int block_pointers[NUM_FILES];
    int used = false;
};


int main() {
    return 0;
}