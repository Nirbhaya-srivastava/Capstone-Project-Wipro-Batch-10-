#include "explorer.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

namespace fs = std::filesystem;

void Explorer::listFiles(const fs::path& path) {
    std::cout << "\nContents of " << path << ":\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << (fs::is_directory(entry) ? "[DIR]  " : "       ")
                  << entry.path().filename().string() << std::endl;
    }
}

void Explorer::changeDirectory(fs::path& current) {
    std::string dir;
    std::cout << "Enter directory name (.. for parent): ";
    std::cin >> dir;

    fs::path newPath = (dir == "..") ? current.parent_path() : current / dir;

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        current = newPath;
        fs::current_path(current);
    } else {
        std::cout << "Directory not found.\n";
    }
}

void Explorer::copyFile() {
    std::string src, dest;
    std::cout << "Source file: "; std::cin >> src;
    std::cout << "Destination path: "; std::cin >> dest;
    try {
        fs::copy(src, dest, fs::copy_options::overwrite_existing);
        std::cout << "File copied successfully.\n";
    } catch (fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Explorer::moveFile() {
    std::string src, dest;
    std::cout << "Source file: "; std::cin >> src;
    std::cout << "Destination path: "; std::cin >> dest;
    try {
        fs::rename(src, dest);
        std::cout << "File moved successfully.\n";
    } catch (fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Explorer::deleteFile() {
    std::string target;
    std::cout << "Enter file/folder to delete: ";
    std::cin >> target;
    try {
        fs::remove_all(target);
        std::cout << "Deleted successfully.\n";
    } catch (fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Explorer::createFile() {
    std::string name;
    std::cout << "Enter new file name: ";
    std::cin >> name;
    std::ofstream file(name);
    if (file) {
        std::cout << "File created.\n";
    } else {
        std::cout << "Error creating file.\n";
    }
}

void Explorer::createDirectory() {
    std::string name;
    std::cout << "Enter new directory name: ";
    std::cin >> name;
    if (fs::create_directory(name))
        std::cout << "Directory created.\n";
    else
        std::cout << "Error creating directory.\n";
}

void Explorer::searchFile(const fs::path& path, const std::string& name) {
    std::cout << "Searching for \"" << name << "\"...\n";
    for (const auto& p : fs::recursive_directory_iterator(path)) {
        if (p.path().filename() == name)
            std::cout << "Found: " << p.path() << std::endl;
    }
}

void Explorer::changePermissions() {
    std::string filename;
    int mode;
    std::cout << "Enter filename: "; std::cin >> filename;
    std::cout << "Enter permissions in octal (e.g. 755): "; std::cin >> std::oct >> mode;
    if (chmod(filename.c_str(), mode) == 0)
        std::cout << "Permissions changed.\n";
    else
        std::cout << "Failed to change permissions.\n";
}
