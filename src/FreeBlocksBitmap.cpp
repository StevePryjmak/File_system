#include "FreeBlocksBitmap.h"

FreeBlocksBitmap::FreeBlocksBitmap() {
    bitmap.set(); 
}


bool FreeBlocksBitmap::allocateBlock(size_t blockIndex) {
    if (blockIndex >= N_BLOCKS) {
        std::cerr << "Invalid block index!" << std::endl;
        return false;
    }
    if (bitmap.test(blockIndex)) {
        bitmap.reset(blockIndex);
        // std::cout << "Before reset" <<std::endl;
        // bitmap.set(blockIndex, 0);
        // std::cout << "After reset" << << std::endl;
        return true;
    } else {
        std::cerr << "Block is already allocated!" << std::endl;
        return false;
    }
}


bool FreeBlocksBitmap::deallocateBlock(size_t blockIndex) {
    if (blockIndex >= N_BLOCKS) {
        std::cerr << "Invalid block index!" << std::endl;
        return false;
    }
    if (!bitmap.test(blockIndex)) {
        bitmap.set(blockIndex);
        return true;
    } else {
        std::cerr << "Block is already free!" << std::endl;
        return false;
    }
}


bool FreeBlocksBitmap::isBlockFree(size_t blockIndex) const {
    if (blockIndex >= N_BLOCKS) {
        std::cerr << "Invalid block index!" << std::endl;
        return false;
    }
    return bitmap.test(blockIndex);
}


size_t FreeBlocksBitmap::getFreeBlockCount() const {
    return bitmap.count();
}


void FreeBlocksBitmap::printBitmap() const {
    for (size_t i = 0; i < N_BLOCKS; ++i) {
        std::cout << (bitmap.test(i) ? "0" : "*");
        if ((i + 1) % 8 == 0) std::cout << "\n";
    }
    std::cout << std::endl;
}
