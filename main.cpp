// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "storage/storage.hpp"
#include "utils/menu.hpp"      
#include "utils/set_cmd.hpp"   

int main(int argc, char* argv[]) {
    // Проверяем, переданы ли --file и --query (для 2 задания)
    std::string filename = "";
    std::string query = "";

    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            filename = argv[++i];
        } else if (std::strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[++i];
        }
    }

    if (!filename.empty() && !query.empty()) {
        // для 2 таска (множество)
        storage_load(filename);
        std::string result = execute_set_command(query);
        if (!result.empty()) {
            std::cout << result << std::endl;
        }
        storage_save(filename);
        return 0;
    }

    run_all_tasks();
    return 0;
}