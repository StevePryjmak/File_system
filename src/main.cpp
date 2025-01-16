#include <iostream>
#include "FileSystem.h"
#include "constants.h"


#include <sstream>
#include <vector>

// std::pair<std::string, std::vector<std::string>> parseCommand(const std::string& command) {
//     std::istringstream iss(command);
//     std::string cmd;
//     std::vector<std::string> args;
//     iss >> cmd;
//     std::string arg;
//     while (iss >> arg) {
//         args.push_back(arg);
//     }
//     return {cmd, args};
// }

// void executeCommand(FileSystem& fs, const std::string& cmd, const std::vector<std::string>& args, const std::string& command) {
//     if (cmd == "exit") {
//         exit(0);
//     } else if (cmd == "saveFile" && args.size() >= 2) {
//         std::string filename = args[0];
//         std::string content = command.substr(command.find(args[1]));
//         fs.saveFile(filename, std::vector<uint8_t>(content.begin(), content.end()));
//     } else if (cmd == "deleteFile" && args.size() == 1) {
//         std::string filename = args[0];
//         fs.deleteFile(filename);
//     } else if (cmd == "ls") {
//         fs.showFiles();
//     } else if (cmd == "mm") {
//         fs.showMemoryState();
//     } else if (cmd == "importFile" && args.size() == 2) {
//         std::string src = args[0];
//         std::string dest = args[1];
//         fs.importFile(src, dest);
//     } else if (cmd == "exportFile" && args.size() == 2) {
//         std::string src = args[0];
//         std::string dest = args[1];
//         fs.exportFile(src, dest);
//     } else {
//         std::cout << "Unknown or invalid command: " << command << std::endl;
//     }
// }

// void interactiveShell(FileSystem& fs) {
//     std::string command;
//     while (true) {
//         std::cout << "fs> ";
//         std::getline(std::cin, command);
//         auto [cmd, args] = parseCommand(command);
//         executeCommand(fs, cmd, args, command);
//     }
// }

// int main() {
//     FileSystem fs = FileSystem();
//     interactiveShell(fs);
//     return 0;
// }

int main() {
    FileSystem fs = FileSystem();
    fs.saveFile("test.txt", std::vector<uint8_t>(48, 'a'));
    // fs.saveFile("test2.txt", std::vector<uint8_t>(1024, 'b'));
    fs.showFiles();
    fs.showMemoryState();
    // fs.deleteFile("test.txt");
    fs.showFiles();
    fs.showMemoryState();
    fs.saveFile("test3.txt", std::vector<uint8_t>(48, 'c'));
    fs.showFiles();
    fs.showMemoryState();
    fs.importFile("test2.txt", "test2.txt");
    fs.exportFile("test2.txt", "test2_exported.txt");
    // fs.saveDisk(FILE_SYSTEM_FILE);
    // fs.saveDisk();
    return 0;
}