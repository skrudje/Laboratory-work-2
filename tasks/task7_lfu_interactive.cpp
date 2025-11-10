// tasks/task7_lfu_interactive.cpp
#include "task7_lfu_interactive.hpp"
#include "../storage/storage.hpp"
#include <iostream>
#include <string>

void task7_run_interactive() {
    if (!g_lfu) {
        int cap;
        std::cout << "Введите ёмкость LFU-кэша: ";
        std::cin >> cap;
        g_lfu = lfu_create(cap);
    }

    std::string cmd;
    std::string key, value;

    while (true) {
        std::cout << "Команда (LFU_SET/LFU_GET/quit): ";
        std::cin >> cmd;

        if (cmd == "quit") break;

        if (cmd == "LFU_SET") {
            std::cout << "Ключ: ";
            std::cin >> key;
            std::cout << "Значение: ";
            std::cin >> value;
            lfu_set(g_lfu, key, value);
            std::cout << "Установлено.\n";
        }
        else if (cmd == "LFU_GET") {
            std::cout << "Ключ: ";
            std::cin >> key;
            std::string val = lfu_get(g_lfu, key);
            std::cout << "Значение: " << val << std::endl;
        }
        else {
            std::cout << "Неизвестная команда.\n";
        }
    }
}