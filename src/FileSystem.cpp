#include "FileSystem.h"
#include <fstream>

FileSystem::FileSystem() {
    superblock = Superblock();
    for (auto &inode : inodes) {
        inode = Inode();
    }
    free_blocks_bitmap = FreeBlocksBitmap();
    for (auto &data_block : data_blocks) {
        data_block = DataBlock();
    }
}

void FileSystem::saveToFile(const std::string &path) {
    std::ofstream file(path);
    file.write(reinterpret_cast<char *>(this), sizeof(FileSystem));
    file.close();
}

FileSystem *FileSystem::loadFromFile(const std::string &path) {
    std::ifstream file(path);
    auto system = new FileSystem();
    file.read(reinterpret_cast<char *>(system), sizeof(FileSystem));
    return system;
}