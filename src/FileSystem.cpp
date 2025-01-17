#include "FileSystem.h"



FileSystem::FileSystem(std::string diskLocation) {
    superblock = Superblock();
    this->diskLocation = diskLocation;
    for (auto &inode : inodes) {
        inode = INode();
    }
    free_blocks_bitmap = FreeBlocksBitmap();
    for (auto &data_block : data_blocks) {
        data_block = DataBlock();
    }
    saveDisk(diskLocation);
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
    if(findINode(filename)) {
        std::cerr << "File with the same name already exists!" << std::endl;
        return;
    }
    auto inode = INode();
    strncpy(inode.name, filename.c_str(), filename.size());
    size_t blocks_needed = data.size() / BLOCK_SIZE + 1;
    size_t blocks_allocated = 0;
    for (size_t i = 0; i < NUM_BLOCKS && blocks_allocated < blocks_needed; ++i) {
        if (free_blocks_bitmap.isBlockFree(i)) {
            inode.block_pointers[blocks_allocated] = i;
            blocks_allocated++;
        }
    }
    inode.size = blocks_needed * BLOCK_SIZE;
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
    // std::cout << "data: " ;
    // for (const auto &byte : data) {
    //     std::cout << static_cast<char>(byte) << "";
    // }
    // std::cout <<std::endl << "Data size: " << data.size() << std::endl;
    for(int i = 0; i < blocks_allocated; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            // std::cout << data[i * BLOCK_SIZE + j] << " ";
            // std::cout << i * BLOCK_SIZE + j << " ";
            if(i * BLOCK_SIZE + j >= data.size()) {
                data_blocks[inode.block_pointers[i]].data[j] = ' ';
                continue;
            }
            data_blocks[inode.block_pointers[i]].data[j] = (char) data[i * BLOCK_SIZE + j];
        }
        free_blocks_bitmap.allocateBlock(inode.block_pointers[i]);
        // data_blocks[inode.block_pointers[i]].data[] = data.data() + i * BLOCK_SIZE;
        // std::copy(data.begin() + i * BLOCK_SIZE, data.begin() + (i + 1) * BLOCK_SIZE, data_blocks[inode.block_pointers[i]].data);
    }
    // Write the data into the allocated blocks
    // size_t data_offset = 0;
    // for (size_t block_index = 0; block_index < blocks_allocated; ++block_index) {
    //     size_t block_id = inode.block_pointers[block_index];
    //     size_t bytes_to_write = BLOCK_SIZE; // std::min(BLOCK_SIZE, (int)(data.size() - data_offset));

    //     // Copy the data to the block
    //     std::copy(data.begin() + data_offset, 
    //               data.begin() + data_offset + bytes_to_write, 
    //               data_blocks[block_id].data);

    //     data_offset += bytes_to_write;
    // }


    // Save the inode metadata to the inode table
    // for (auto &existing_inode : inodes) {
    //     if (!existing_inode.used) {
    //         existing_inode = inode;
    //         existing_inode.used = true;
    //         break;
    //     }
    // }

    saveDisk(diskLocation);
}



void FileSystem::deleteFile(const std::string &filename) {
    for (auto &inode: inodes) {
        if (inode.used && filename == inode.name) {
            inode.used = false;
            for (size_t i = 0; i < inode.size / BLOCK_SIZE + 1; ++i) {
                if (!free_blocks_bitmap.isBlockFree(inode.block_pointers[i])) {
                    free_blocks_bitmap.deallocateBlock(inode.block_pointers[i]);
                }
            }
        }
    }
    saveDisk(diskLocation);
}

void FileSystem::setDiskLocation(const std::string &path) {
    diskLocation = path;
}

void FileSystem::importFile(const std::string &external_filename, const std::string &internal_filename) {
    std::ifstream file(external_filename, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return;
    }
    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(size);
    std::cout << std::dec << std::endl;
    file.read(reinterpret_cast<char *>(data.data()), size);
    // std::cout << "data: ";
    // for (const auto &byte : data) {
    //     std::cout << static_cast<char>(byte) << "";
    // }
    file.close();
    saveFile(internal_filename, data);
}


void FileSystem::exportFile(const std::string &internal_filename, const std::string &external_filename) {
    INode* inode = findINode(internal_filename);
    if (!inode) {
        std::cerr << "File not found!" << std::endl;
        return;
    }
    std::ofstream file(external_filename, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return;
    }
    for (size_t i = 0; i < inode->size / BLOCK_SIZE; ++i) {
        file.write(data_blocks[inode->block_pointers[i]].data, BLOCK_SIZE);
    }
    file.close();
}


void FileSystem::showFiles() {
    for (auto &inode : inodes) {
        if (inode.used) {
            std::cout << inode.name << "\t" << inode.size << " bytes" << std::endl;
        }
    }
}


void FileSystem::showMemoryState() {
    std::cout << "Free blocks: " << free_blocks_bitmap.getFreeBlockCount() << std::endl;
    free_blocks_bitmap.printBitmap();
}


void FileSystem::saveDisk(const std::string &path) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return;
    }
    file.write(reinterpret_cast<char *>(&superblock), sizeof(superblock));
    file.write(reinterpret_cast<char *>(inodes), sizeof(inodes));
    file.write(reinterpret_cast<char *>(&free_blocks_bitmap), sizeof(free_blocks_bitmap));
    file.write(reinterpret_cast<char *>(data_blocks), sizeof(data_blocks));
    file.close();
}


std::string FileSystem::readFile(const std::string &filename) {
    INode* inode = findINode(filename);
    if (!inode) {
        std::cout << "File not found!" << std::endl;
        return "File not found!";
    }
    std::string data;
    for (size_t i = 0; i < inode->size / BLOCK_SIZE; ++i) {
        data.append(data_blocks[inode->block_pointers[i]].data, BLOCK_SIZE);
    }
    return data;
}


FileSystem *FileSystem::loadDisk(const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Could not open file!" << std::endl;
        return nullptr;
    }
    auto system = new FileSystem();
    file.read(reinterpret_cast<char *>(&system->superblock), sizeof(system->superblock));
    file.read(reinterpret_cast<char *>(system->inodes), sizeof(system->inodes));
    file.read(reinterpret_cast<char *>(&system->free_blocks_bitmap), sizeof(system->free_blocks_bitmap));
    file.read(reinterpret_cast<char *>(system->data_blocks), sizeof(system->data_blocks));
    system->diskLocation = path;
    file.close();
    // std::cout << "Disk location: " << system->diskLocation << std::endl;
    return system;
}


INode *FileSystem::findINode(const std::string &filename) {
    for (auto &inode : inodes) {
        if (inode.used && filename == inode.name) {
            return &inode;
        }
    }
    return nullptr;
}