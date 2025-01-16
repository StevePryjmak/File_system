#include <iostream>
#include "FileSystem.h"
#include "constants.h"


int main() {
    FileSystem fs = FileSystem();
    fs.saveToFile(FILE_SYSTEM_FILE);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}