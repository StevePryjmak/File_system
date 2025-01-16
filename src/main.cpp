#include <iostream>

const int BLOCK_SIZE = 512;
const int NUM_BLOCKS = 48;
const int NUM_INODES = 16;

struct Superblock {
    int magic;
    int num_blocks;
    int free_blocks ;
    int inode_start = 1;
};


int main() {
    return 0;
}