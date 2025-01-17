#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <cstdio>
#include "constants.h"
#include "Superblock.h"
#include "Inode.h"
#include "FreeBlocksBitmap.h"
#include "DataBlock.h"

class FileSystem {
private:
    Superblock superblock;
    INode inodes[NUM_INODES];
    FreeBlocksBitmap free_blocks_bitmap;
    DataBlock data_blocks[NUM_BLOCKS];

    INode *findINode(const std::string &filename);
public:
    std::string diskLocation;
    FileSystem(std::string diskLocation = FILE_SYSTEM_FILE);

    void showFiles();
    void showMemoryState();

    /**
     * Import a file from the external filesystem into the internal filesystem
     * @param external_filename - name of the file in the external filesystem
     * @param internal_filename - name to be used for the file in the internal filesystem
     */
    void importFile(const std::string &external_filename, const std::string &internal_filename);

    /**
     * Export a file from the internal filesystem to the external filesystem
     * @param internal_filename - name of the file in the internal filesystem
     * @param external_filename - name to be used for the file in the external filesystem
     */
    void exportFile(const std::string &internal_filename, const std::string &external_filename);

    /**
     * Save file to the filesystem
     * @param filename - name of the file
     * @param data - data to be saved
     */
    void saveFile(const std::string& filename, const std::vector<uint8_t>& data);
    void deleteFile(const std::string& filename);
    std::string readFile(const std::string& filename);

    /** 
     * Filesystem configuration file functions 
     * @param path - path to the file
     * @return Filesystem object
     */
    void saveDisk(const std::string &path);
    static FileSystem *loadDisk(const std::string &path);
    void setDiskLocation(const std::string &path);
    

    /**
     * Remove the disk file from the filesystem
     * @param path - path to the disk file
     */

    template<typename T>
    void writeStruct(const T& data, int blockIndex);
};

