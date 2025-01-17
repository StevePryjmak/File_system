#include <iostream>
#include <sstream>
#include <vector>
#include "FileSystem.h"


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
    std::cout << "  saveFile <filename> <content> - Save a file with the specified content\n";
    std::cout << "  deleteFile <filename> - Delete the specified file\n";
    std::cout << "  ls - List all files in the file system\n";
    std::cout << "  mm - Show memory state of the file system\n";
    std::cout << "  importFile <src> <dest> - Import a file from the host file system\n";
    std::cout << "  exportFile <src> <dest> - Export a file to the host file system\n";
    std::cout << "  help - Show this help message\n\n";
}

bool executeCommand(FileSystem* fs, const std::string& cmd, const std::vector<std::string>& args, const std::string& command) {
    std::cout << "Disk Location: " << fs->diskLocation << std::endl;
    if (cmd == "exit") {
        return false;
    } else if (cmd == "saveFile" && args.size() >= 2) {
        std::string filename = args[0];
        std::string content = command.substr(command.find(args[1]));
        fs->saveFile(filename, std::vector<uint8_t>(content.begin(), content.end()));
    } else if (cmd == "deleteFile" && args.size() == 1) {
        std::string filename = args[0];
        fs->deleteFile(filename);
    } else if (cmd == "ls") {
        fs->showFiles();
    } else if (cmd == "mm") {
        fs->showMemoryState();
    } else if (cmd == "importFile" && args.size() == 2) {
        std::string src = args[0];
        std::string dest = args[1];
        fs->importFile(src, dest);
    } else if (cmd == "exportFile" && args.size() == 2) {
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

void runPreaperedCommand(FileSystem* fs) {
    // Create a file
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Create a file test" << std::endl<< std::endl;
    executeCommand(fs, "ls", {}, "ls");
    executeCommand(fs, "saveFile test.txt test content", {"test.txt", "test content"}, "saveFile test.txt test content");
    executeCommand(fs, "ls", {}, "ls");
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    // Delete the file
    std::cout << "Delete a file test" << std::endl << std::endl;
    executeCommand(fs, "deleteFile test.txt", {"test.txt"}, "deleteFile test.txt");
    executeCommand(fs, "ls", {}, "ls");
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    // Import a file
    std::cout << "Import a file test" << std::endl << std::endl;
    executeCommand(fs, "importFile /path/to/external/file.txt imported_file.txt", {"/path/to/external/file.txt", "imported_file.txt"}, "importFile /path/to/external/file.txt imported_file.txt");
    executeCommand(fs, "ls", {}, "ls");
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    // Export a file
    std::cout << "Export a file test" << std::endl << std::endl;
    executeCommand(fs, "exportFile imported_file.txt /path/to/exported/file.txt", {"imported_file.txt", "/path/to/exported/file.txt"}, "exportFile imported_file.txt /path/to/exported/file.txt");
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;    
    // Show memory state
    std::cout << "Show memory state test" << std::endl << std::endl;
    executeCommand(fs, "mm", {}, "mm");
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    // Attempt to save a file with a name that is too long
    std::cout << "Save file with a name that is too long test" << std::endl << std::endl;
    std::string long_filename(300, 'a'); // Create a long filename
    executeCommand(fs, "saveFile " + long_filename + " content", {long_filename, "content"}, "saveFile " + long_filename + " content");
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    // Attempt to save a file that is too large
    std::cout << "Save file that is too large test" << std::endl << std::endl;
    std::vector<uint8_t> large_content(1024 * 1024 * 10, 'a'); // Create large content
    executeCommand(fs, "saveFile large_file.txt " + std::string(large_content.begin(), large_content.end()), {"large_file.txt", std::string(large_content.begin(), large_content.end())}, "saveFile large_file.txt large_content");
    std::cout << "-------------------------------------------------" << std::endl;


}

void interactiveShell(FileSystem* fs) {
    std::cout << "Interact:diskLocation: " << fs->diskLocation << std::endl;
    std::string command;
    bool run = true;

    while (run) {
        std::cout << "\nfs> ";
        std::getline(std::cin, command);
        auto [cmd, args] = parseCommand(command);
        run = executeCommand(fs, cmd, args, command);
    }
}
