#pragma once
#include "constants.h"

struct Superblock {
    int magic = 0xf0f03410;
    int num_blocks = NUM_BLOCKS;
    int free_blocks = NUM_BLOCKS;
    int inode_start = 1;
};
