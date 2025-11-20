// tasks/task4_subarray.cpp
#include "task4_subarray.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

void task4_run() {
    std::cout << "Поиск подмассива с заданной суммой\n";

    // Ввод элементов массива
    std::cout << "Введите элементы массива (через пробел, только целые числа): ";
    std::string line;
    std::getline(std::cin >> std::ws, line);

    // Парсинг строки
    std::vector<int> nums;
    std::stringstream ss(line);
    std::string token;
    while (ss >> token) {
        try {
            int num = std::stoi(token);
            nums.push_back(num);
        } catch (...) {
            // игнор некорректных значений
        }
    }

    if (nums.empty()) {
        std::cout << "Не введено ни одного числа.\n";
        return;
    }

    int target;
    std::cout << "Введите целевую сумму: ";
    std::cin >> target;

    // Поиск всех подмассивов
    std::unordered_map<int, std::vector<int>> prefix_sum_indices;
    prefix_sum_indices[0] = {-1}; // для подмассива с начала
    int current_sum = 0;
    bool found = false;

    for (int i = 0; i < nums.size(); ++i) {
        current_sum += nums[i];

        if (prefix_sum_indices.find(current_sum - target) != prefix_sum_indices.end()) {
            // Найдены все индексы, где была сумма current_sum - target
            for (int start : prefix_sum_indices[current_sum - target]) {
                int end = i;
                // Вывод подмассива в формате [a, b, c]
                std::cout << "[";
                for (int j = start + 1; j <= end; ++j) {
                    std::cout << nums[j];
                    if (j < end) std::cout << ", ";
                }
                std::cout << "]\n" << std::endl;
                found = true;
            }
        }

        // Добавляем текущий индекс к списку индексов для этой суммы
        prefix_sum_indices[current_sum].push_back(i);
    }

    if (!found) {
        std::cout << "Подмассив с такой суммой не найден.\n";
    }
}