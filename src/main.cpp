#include <iostream>
#include "FileSystem.h"
#include "constants.h"


int main() {
    FileSystem fs = FileSystem();
    std::cout << "Hello, World!" << std::endl;
    fs.saveFile("test.txt", std::vector<uint8_t>(1024, 'a'));
    fs.saveFile("test2.txt", std::vector<uint8_t>(1024, 'b'));
    fs.showFiles();
    fs.showMemoryState();
    fs.saveToFile(FILE_SYSTEM_FILE);
    fs.deleteFile("test.txt");
    fs.showFiles();
    fs.showMemoryState();
    fs.saveFile("test3.txt", std::vector<uint8_t>(2048, 'c'));
    fs.showFiles();
    fs.showMemoryState();
    return 0;
}