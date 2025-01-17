#include <iostream>
#include "FileSystem.h"
#include "constants.h"
#include <sstream>
#include <vector>
#include <filesystem>
#include "FileSystemShell.cpp"


void removeDisk(const std::string &path) {
    std::string fullPath = "partitions/" + path;
    if (std::remove(fullPath.c_str()) != 0) {
        perror("Error deleting file");
    } else {
        std::cout << "File successfully deleted" << std::endl;
    }
}

void createNewDisk(const std::string &path) {
    std::filesystem::create_directory("partitions");
    FileSystem fs("partitions/" + path + ".myfs");
    fs.saveDisk("partitions/" + path + ".myfs");
}

void showDisks() {
    std::filesystem::create_directory("partitions");
    for (const auto &entry : std::filesystem::directory_iterator("partitions")) {
        std::cout << entry.path().filename().string() << std::endl;
    }
}

void printHelp() {
    std::cout << "Available commands:\n";
    std::cout << "  exit - Exit the program\n";
    std::cout << "  removeDisk <path> - Remove the disk at the specified path\n";
    std::cout << "  createDisk <path> - Create a new disk at the specified path\n";
    std::cout << "  run <path> - Open the interactive shell for the specified disk\n";
    std::cout << "  showDisks - Show all available disks\n";
    std::cout << "  test - Run a set of preapered commands\n";
    std::cout << "  help - Show this help message\n\n";
}

void mainShell() {
    std::string command;
    while (true) {
        std::cout << "\nmain> ";
        std::getline(std::cin, command);
        auto [cmd, args] = parseCommand(command);
        if (cmd == "exit") {
            exit(0);
        } else if (cmd == "removeDisk" && args.size() == 1) {
            removeDisk(args[0]);
        } else if (cmd == "createDisk" && args.size() == 1) {
            createNewDisk(args[0]);
        } else if (cmd == "run" && args.size() == 1) {
            interactiveShell(FileSystem::loadDisk("partitions/" + args[0]));
        } else if (cmd == "help") {
            printHelp();
        } else if(cmd == "showDisks") {
            showDisks();
        }
        else if(cmd == "test") {
            createNewDisk("test");
            runPreparedCommand(FileSystem::loadDisk("partitions/test.myfs"));
        }
        else {
            std::cout << "Unknown or invalid command: " << command << std::endl;
            std::cout << "Type 'help' for a list of available commands." << std::endl;
        }
    }
}

int main() {
    mainShell();
    return 0;
}
