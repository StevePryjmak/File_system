#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
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

    void showFiles();
    void showMemoryState();
    /**
     * Save file to the filesystem
     * @param filename - name of the file
     * @param data - data to be saved
     */
    void saveFile(const std::string& filename, const std::vector<uint8_t>& data);
    /** 
     * Filesystem configuration file functions 
     * @param path - path to the file
     * @return Filesystem object
     */
    void saveToFile(const std::string &path);
    static FileSystem *loadFromFile(const std::string &path);
};



