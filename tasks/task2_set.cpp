// tasks/task2_set.cpp
#include "task2_set.hpp"
#include "../storage/storage.hpp"
#include <iostream>
#include <string>

void task2_run() {
    std::string setname;
    std::cout << "Введите имя множества: ";
    std::cin >> setname;

    Set* s = get_or_create_set(setname);

    std::string cmd;
    std::string value;

    while (true) {
        std::cout << "Команда (SADD/SDEL/SISMEMBER/quit): ";
        std::cin >> cmd;

        if (cmd == "quit") break;

        std::cout << "Значение: ";
        std::cin >> value;

        if (cmd == "SADD") {
            bool added = set_add(s, value);
            std::cout << (added ? "Добавлено." : "Уже есть.") << std::endl;
        }
        else if (cmd == "SDEL") {
            bool removed = set_del(s, value);
            std::cout << (removed ? "Удалено." : "Нет в множестве.") << std::endl;
        }
        else if (cmd == "SISMEMBER") {
            bool exists = set_has(s, value);
            std::cout << (exists ? "Есть." : "Нет.") << std::endl;
        }
        else {
            std::cout << "Неизвестная команда.\n";
        }
    }
}