#include <iostream>
#include <sstream>
#include <vector>
#include "FileSystem.h"
#include <chrono>
#include <thread>


std::pair<std::string, std::vector<std::string>> parseCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    std::vector<std::string> args;
    iss >> cmd;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return {cmd, args};
}

void printFSHelp() {
    std::cout << "File System Commands:\n";
    std::cout << "  exit - Exit the interactive shell\n";
    std::cout << "  save <filename> <content> - Save a file with the specified content\n";
    std::cout << "  cat <filename> - Display the content of the specified file\n";
    std::cout << "  remove <filename> - Delete the specified file\n";
    std::cout << "  ls - List all files in the file system\n";
    std::cout << "  mm - Show memory state of the file system\n";
    std::cout << "  import <src> <dest> - Import a file from the host file system\n";
    std::cout << "  export <src> <dest> - Export a file to the host file system\n";
    std::cout << "  help - Show this help message\n\n";
}

bool executeCommand(FileSystem* fs, const std::string& cmd, const std::vector<std::string>& args, const std::string& command) {
    // std::cout << "Disk Location: " << fs->diskLocation << std::endl;
    if (cmd == "exit") {
        return false;
    } else if (cmd == "save" && args.size() >= 2) {
        std::string filename = args[0];
        std::string content = command.substr(command.find(args[1]));
        fs->saveFile(filename, std::vector<uint8_t>(content.begin(), content.end()));
    } else if(cmd== "cat" && args.size()>=1) {
        std::cout <<fs->readFile(args[0])<< std::endl;
    } else if (cmd == "remove" && args.size() == 1) {
        std::string filename = args[0];
        fs->deleteFile(filename);
    } else if (cmd == "ls") {
        fs->showFiles();
    } else if (cmd == "mm") {
        fs->showMemoryState();
    } else if (cmd == "import" && args.size() == 2) {
        std::string src = args[0];
        std::string dest = args[1];
        fs->importFile(src, dest);
    } else if (cmd == "export" && args.size() == 2) {
        std::string src = args[0];
        std::string dest = args[1];
        fs->exportFile(src, dest);
    } else if (cmd == "help") {
        printFSHelp();
    } else {
        std::cout << "Unknown or invalid command: " << command << std::endl;
        std::cout << "Type 'help' for a list of available commands." << std::endl;
    }
    return true;
}

void doCommand(FileSystem* fs, const std::string& command) {
    std::cout << "\nfs> "<< command << std::endl;
    auto [cmd, args] = parseCommand(command);
    executeCommand(fs, cmd, args, command);
    // std::this_thread::sleep_for(std::chrono::seconds(5));
}

void runPreparedCommand(FileSystem* fs) {
    // Create a file
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "Create a file test" << std::endl << std::endl;
    doCommand(fs, "ls");
    doCommand(fs, "save test.txt test_content");
    doCommand(fs, "save test2.txt long_text_long_text_2_bytes");
    doCommand(fs, "ls");
    doCommand(fs, "mm");
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    // Delete the file
    std::cout << "Delete a file test" << std::endl << std::endl;
    doCommand(fs, "deleteFile test.txt");
    doCommand(fs, "ls");
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    // Import a file
    std::cout << "Import a file test" << std::endl << std::endl;
    doCommand(fs, "importFile /path/to/external/file.txt imported_file.txt");
    doCommand(fs, "ls");
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    // Export a file
    std::cout << "Export a file test" << std::endl << std::endl;
    doCommand(fs, "exportFile imported_file.txt /path/to/exported/file.txt");
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;    
    // Show memory state
    std::cout << "Show memory state test" << std::endl << std::endl;
    doCommand(fs, "mm");
    std::cout << "----------------------------------------------------------------" << std::endl;
}

void interactiveShell(FileSystem* fs) {
    // std::cout << "Interact:diskLocation: " << fs->diskLocation << std::endl;
    std::string command;
    bool run = true;

    while (run) {
        std::cout << "\nfs> ";
        std::getline(std::cin, command);
        auto [cmd, args] = parseCommand(command);
        run = executeCommand(fs, cmd, args, command);
    }
}
