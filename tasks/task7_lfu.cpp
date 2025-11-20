// tasks/task7_lfu.cpp
#include "task7_lfu.hpp"
#include "../storage/storage.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

void task7_run() {
    int cap, q;
    std::cout << "cap = ";
    std::cin >> cap;
    std::cout << "Q = ";
    std::cin >> q;
    std::cout << std::endl;

    // Создаем кэш
    if (!g_lfu) {
        g_lfu = lfu_create(cap);
    }

    std::cout << "Команды: SET x y | GET x" << std::endl;

    std::cin.ignore(); // съедаем символ новой строки после Q
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> commands;

    while (iss >> token) {
        commands.push_back(token);
    }

    std::vector<std::string> get_results;

    for (size_t i = 0; i < commands.size(); ) {
        std::string cmd = commands[i++];

        if (cmd == "SET" && i + 1 < commands.size()) {
            std::string key = commands[i++];
            std::string value = commands[i++];
            if (g_lfu) {
                lfu_set(g_lfu, key, value);
            }
        }
        else if (cmd == "GET" && i < commands.size()) {
            std::string key = commands[i++];
            if (g_lfu) {
                std::string val = lfu_get(g_lfu, key);
                get_results.push_back(val);
            } else {
                get_results.push_back("-1");
            }
        }
        else {
        }
    }

    // результаты GET запросов
    std::cout << "Вывод: ";
    for (size_t i = 0; i < get_results.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << get_results[i];
    }
    if (!get_results.empty()) std::cout << "\n" << std::endl;
}