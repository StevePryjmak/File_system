#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FILE_SYSTEM_FILE "filesystem.txt"
#define FILE_NAME_MAX_LENGTH 32
#include <algorithm>


const int BLOCK_SIZE = 128;
const int NUM_BLOCKS = 32;
const int NUM_INODES = 16;
const int NUM_FILES = 16;
const int MAX = std::min(BLOCK_SIZE * NUM_FILES, BLOCK_SIZE * NUM_BLOCKS);

#define FILE_MAX_SIZE MAX


#endif // CONSTANTS_H