#pragma once
#include "constants.h"

struct Inode {
    char name[50];
    int size;
    int block_pointers[NUM_FILES];
    int used = false;
};
