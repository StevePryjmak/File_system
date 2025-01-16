#pragma once
#include "constants.h"

struct INode {
    char name[50];
    int size;
    int block_pointers[NUM_FILES];
    int used = false;
};
