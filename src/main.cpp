#include <iostream>
#include "FileSystem.h"
#include "constants.h"


int main() {
    FileSystem fs = FileSystem();
    fs.saveToFile(FILE_SYSTEM_FILE);
    std::cout << "Hello, World!" << std::endl;
    fs.saveFile("test.txt", std::vector<uint8_t>(1024, 'a'));
    fs.showFiles();
    fs.showMemoryState();
    return 0;
}