#ifndef FREEBLOCKSBITMAP_H
#define FREEBLOCKSBITMAP_H

#include <bitset>
#include <iostream>
#include "constants.h"
#define N_BLOCKS NUM_BLOCKS

class FreeBlocksBitmap {
private:
    std::bitset<N_BLOCKS> bitmap;

public:
    FreeBlocksBitmap();
    bool allocateBlock(size_t blockIndex);
    bool deallocateBlock(size_t blockIndex);
    bool isBlockFree(size_t blockIndex) const;
    size_t getFreeBlockCount() const;
    void printBitmap() const;
};

#endif // FREEBLOCKSBITMAP_H
