#ifndef FREEBLOCKSBITMAP_H
#define FREEBLOCKSBITMAP_H

#include <bitset>
#include <iostream>

#define N_BLOCKS 48 // @TODO remove this leter

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
