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

// Works but need to be refactored SRP principle not followed
void FileSystem::saveFile(const std::string& filename, const std::vector<uint8_t>& data) {
    if (filename.size() > FILE_NAME_MAX_LENGTH) {
        std::cerr << "Filename is too long!" << std::endl;
        return;
    }
    if (data.size() > FILE_MAX_SIZE) {
        std::cerr << "File is too big!" << std::endl;
        return;
    }
    for (const auto &inode : inodes) {
        if (inode.used && filename == inode.name) {
            std::cerr << "File with the same name already exists!" << std::endl;
            return;
        }
    }
    auto inode = Inode();
    strncpy(inode.name, filename.c_str(), FILE_NAME_MAX_LENGTH);
    inode.size = data.size();
    size_t blocks_needed = inode.size / BLOCK_SIZE + 1;
    size_t blocks_allocated = 0;
    for (size_t i = 0; i < NUM_BLOCKS && blocks_allocated < blocks_needed; ++i) {
        if (free_blocks_bitmap.isBlockFree(i)) {
            inode.block_pointers[blocks_allocated] = i;
            free_blocks_bitmap.allocateBlock(i);
            blocks_allocated++;
        }
    }
    if (blocks_allocated < blocks_needed) {
        std::cerr << "Not enough space to save file!" << std::endl;
        return;
    }
    for (auto &existing_inode : inodes) {
        if (!existing_inode.used) {
            existing_inode = inode;
            existing_inode.used = true;
            break;
        }
    }
    for (size_t i = 0; i < blocks_allocated; ++i) {
        for (size_t j = 0; j < BLOCK_SIZE && (i * BLOCK_SIZE + j) < inode.size; ++j) {
            data_blocks[inode.block_pointers[i]].data[j] = data[i * BLOCK_SIZE + j];
        }
    }
}

void FileSystem::deleteFile(const std::string &filename) {
    for (auto &inode: inodes) {
        if (inode.used && filename == inode.name) {
            inode.used = false;
            for (size_t i = 0; i < inode.size / BLOCK_SIZE + 1; ++i) {
                free_blocks_bitmap.deallocateBlock(inode.block_pointers[i]);
            }
        }
    }
}

void FileSystem::importFile(const std::string &filename) {
    std::ifstream
            file(filename, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return;
    }
    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(size);
    file.read(reinterpret_cast<char *>(data.data()), size);
    file.close();
    saveFile(filename, data);
}

void FileSystem::showFiles() {
    for (auto &inode : inodes) {
        if (inode.used) {
            std::cout << inode.name << std::endl;
        }
    }
}

void FileSystem::showMemoryState() {
    std::cout << "Free blocks: " << free_blocks_bitmap.getFreeBlockCount() << std::endl;
    free_blocks_bitmap.printBitmap();
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