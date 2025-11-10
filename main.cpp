// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "storage/storage.hpp"
#include "utils/menu.hpp"      // содержит run_all_tasks()
#include "utils/set_cmd.hpp"   // содержит execute_set_command()

int main(int argc, char* argv[]) {
    // Проверяем, переданы ли --file и --query → режим команды (только задание 2)
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
        // === Режим команды: ТОЛЬКО задание 2 (множество) ===
        storage_load(filename);
        std::string result = execute_set_command(query);
        if (!result.empty()) {
            std::cout << result << std::endl;
        }
        storage_save(filename);
        return 0;
    }

    // === Интерактивный режим: все 7 заданий ===
    run_all_tasks();
    return 0;
}