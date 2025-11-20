// utils/menu.cpp
#include "menu.hpp"
#include <iostream>
#include "../tasks/task1_logic.hpp"
#include "../tasks/task2_set.hpp"
#include "../tasks/task3_partition.hpp"
#include "../tasks/task4_subarray.hpp"
#include "../tasks/task5_huffman.hpp"
#include "../tasks/task61_double_kuku.hpp"
#include "../tasks/task62_restructure.hpp"
#include "../tasks/task7_lfu.hpp"

void run_all_tasks() {
    int choice;
    do {
        std::cout << "\n1. Вычисление логического выражения\n";
        std::cout << "2. Реализация АТД «Множество»\n";
        std::cout << "3. Разбиение множества на схожие подмножества\n";
        std::cout << "4. Поиск подмассива с заданной суммой\n";
        std::cout << "5. Построение кода Хаффмана\n";
        std::cout << "6  Хеш-таблица\n";
        std::cout << "7. Реализация LFU-кэша\n";
        std::cout << "0. Выход\n\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: task1_run(); break;
            case 2: task2_run(); break;
            case 3: task3_run(); break;
            case 4: task4_run(); break;
            case 5: task5_run(); break;
            case 6: {
                int sub_choice;
                std::cout << "Выберите подпункт:\n";
                std::cout << "1. Двойное хеширование и Хеширование кукушки\n";
                std::cout << "2. Реструктуризация\n";
                std::cout << "Ваш выбор: ";
                std::cin >> sub_choice;
                if (sub_choice == 1) {
                    task61_run();
                } else if (sub_choice == 2) {
                    task62_run();
                } else {
                    std::cout << "Неверный выбор.\n";
                }
                break;
            }
            case 7: task7_run(); break;
            case 0: std::cout << "Выход.\n"; break;
            default: std::cout << "Неверный выбор.\n"; break;
        }
    } while (choice != 0);
}