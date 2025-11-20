// tasks/task61_double_kuku.cpp
#include "task61_double_kuku.hpp"
#include "../storage/storage.hpp"
#include "../structures/hash_table_double.h"
#include "../structures/hash_table_kuku.h"
#include <iostream>
#include <string>

void task61_run() {
    std::cout << "Выберите метод хеширования:\n";
    std::cout << "1. Двойное хеширование\n";
    std::cout << "2. Хеширование кукушки\n";
    int method;
    std::cin >> method;

    std::string table_name;
    std::cout << "Введите имя хеш-таблицы: ";
    std::cin >> table_name;

    if (method == 1) {
        // Двойное хеширование
        HashTableDouble* ht = nullptr;
        if (g_hash_tables_double.find(table_name) != g_hash_tables_double.end()) {
            ht = g_hash_tables_double[table_name];
        } else {
            ht = ht_create_double(16);
            g_hash_tables_double[table_name] = ht;
        }

        std::string cmd;
        while (true) {
            std::cout << "Команда (SET/GET/DEL/quit): ";
            std::cin >> cmd;

            if (cmd == "quit") break;

            if (cmd == "SET") {
                std::string key, value;
                std::cout << "Ключ: ";
                std::cin >> key;
                std::cout << "Значение: ";
                std::cin >> value;
                bool added = ht_insert(ht, key, value);
                if (added) {
                    std::cout << "Добавлено.\n";
                } else {
                    std::cout << "Обновлено.\n";
                }
            }
            else if (cmd == "GET") {
                std::string key;
                std::cout << "Ключ: ";
                std::cin >> key;
                std::string val;
                bool found = ht_get(ht, key, val);
                if (found) {
                    std::cout << "Значение: " << val << "\n";
                } else {
                    std::cout << "Значение: -1\n";
                }
            }
            else if (cmd == "DEL") {
                std::string key;
                std::cout << "Ключ: ";
                std::cin >> key;
                bool removed = ht_delete(ht, key);
                if (removed) {
                    std::cout << "Удалено.\n";
                } else {
                    std::cout << "Не найдено.\n";
                }
            }
        }
    }
    else if (method == 2) {
        // Хеширование кукушки
        HashTableKuku* ht = nullptr;
        if (g_hash_tables_kuku.find(table_name) != g_hash_tables_kuku.end()) {
            ht = g_hash_tables_kuku[table_name];
        } else {
            ht = ht_create_kuku(16);
            g_hash_tables_kuku[table_name] = ht;
        }

        std::string cmd;
        while (true) {
            std::cout << "Команда (SET/GET/DEL/quit): ";
            std::cin >> cmd;

            if (cmd == "quit") break;

            if (cmd == "SET") {
                std::string key, value;
                std::cout << "Ключ: ";
                std::cin >> key;
                std::cout << "Значение: ";
                std::cin >> value;
                bool added = ht_insert(ht, key, value);
                if (added) {
                    std::cout << "Добавлено.\n";
                } else {
                    std::cout << "Обновлено.\n";
                }
            }
            else if (cmd == "GET") {
                std::string key;
                std::cout << "Ключ: ";
                std::cin >> key;
                std::string val;
                bool found = ht_get(ht, key, val);
                if (found) {
                    std::cout << "Значение: " << val << "\n";
                } else {
                    std::cout << "Значение: -1\n";
                }
            }
            else if (cmd == "DEL") {
                std::string key;
                std::cout << "Ключ: ";
                std::cin >> key;
                bool removed = ht_delete(ht, key);
                if (removed) {
                    std::cout << "Удалено.\n";
                } else {
                    std::cout << "Не найдено.\n";
                }
            }
        }
    }
}