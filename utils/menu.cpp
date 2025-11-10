// utils/menu.cpp
#include "menu.hpp"
#include <iostream>
#include "../tasks/task1_logic.hpp"
#include "../tasks/task2_set_interactive.hpp"
#include "../tasks/task3_partition.hpp"
#include "../tasks/task4_subarray.hpp"
#include "../tasks/task5_huffman.hpp"
#include "../tasks/task6_hash_test.hpp"
#include "../tasks/task7_lfu_interactive.hpp"

void run_all_tasks() {
    int choice;
    do {
        std::cout << "\n=== Лабораторная работа №2 ===\n\n";
        std::cout << "1. Вычисление логического выражения\n";
        std::cout << "2. Реализация АТД «Множество» (интерактив)\n";
        std::cout << "3. Разбиение множества на схожие подмножества\n";
        std::cout << "4. Поиск подмассива с заданной суммой\n";
        std::cout << "5. Построение кода Хаффмана\n";
        std::cout << "6. Эмпирический анализ хеш-таблиц\n";
        std::cout << "7. Реализация LFU-кэша (интерактив)\n";
        std::cout << "0. Выход\n\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: task1_run(); break;
            case 2: task2_run_interactive(); break;
            case 3: task3_run(); break;
            case 4: task4_run(); break;
            case 5: task5_run(); break;
            case 6: task6_run(); break;
            case 7: task7_run_interactive(); break;
            case 0: std::cout << "Выход.\n"; break;
            default: std::cout << "Неверный выбор.\n"; break;
        }
    } while (choice != 0);
}