#include "explorer.h"
#include <iostream>
#include <filesystem>

int main() {
    Explorer exp;
    std::filesystem::path current = std::filesystem::current_path();

    while (true) {
        std::cout << "\n=== Simple File Explorer ===\n";
        std::cout << "Current Directory: " << current << "\n";
        std::cout << "1. List Files\n2. Change Directory\n3. Copy File\n4. Move File\n"
                     "5. Delete File\n6. Create File\n7. Create Directory\n8. Search File\n"
                     "9. Change Permissions\n10. Exit\n> ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: exp.listFiles(current); break;
            case 2: exp.changeDirectory(current); break;
            case 3: exp.copyFile(); break;
            case 4: exp.moveFile(); break;
            case 5: exp.deleteFile(); break;
            case 6: exp.createFile(); break;
            case 7: exp.createDirectory(); break;
            case 8: {
                std::string name;
                std::cout << "Enter filename to search: ";
                std::cin >> name;
                exp.searchFile(current, name);
                break;
            }
            case 9: exp.changePermissions(); break;
            case 10: std::cout << "Exiting..." << std::endl;
                 return 0;
            default: std::cout << "Invalid option.\n"; break;
        }
    }
}
