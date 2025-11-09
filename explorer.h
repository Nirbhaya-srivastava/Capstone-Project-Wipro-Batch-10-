#ifndef EXPLORER_H
#define EXPLORER_H

#include <string>
#include <filesystem>

class Explorer {
public:
    void listFiles(const std::filesystem::path& path);
    void changeDirectory(std::filesystem::path& current);
    void copyFile();
    void moveFile();
    void deleteFile();
    void createFile();
    void createDirectory();
    void searchFile(const std::filesystem::path& path, const std::string& name);
    void changePermissions();
};

#endif
