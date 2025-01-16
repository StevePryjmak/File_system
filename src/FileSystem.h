#pragma once
#include <string>
#include "constants.h"
#include "Superblock.h"
#include "Inode.h"
#include "FreeBlocksBitmap.h"
#include "DataBlock.h"


class FileSystem {
private:
    Superblock superblock;
    Inode inodes[NUM_INODES];
    FreeBlocksBitmap free_blocks_bitmap;
    DataBlock data_blocks[NUM_BLOCKS];
public:
    FileSystem();

    /** 
     * Filesystem configuration file functions 
     * @param path - path to the file
     * @return Filesystem object
     */
    void saveToFile(const std::string &path);
    static FileSystem *loadFromFile(const std::string &path);
};



