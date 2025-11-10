// tasks/task4_subarray.cpp
#include "task4_subarray.hpp"
#include "../storage/storage.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

void task4_run() {
    std::string arrname;
    std::cout << "Введите имя массива: ";
    std::cin >> arrname;

    Array* arr = g_arrays[arrname];
    if (!arr) {
        std::cout << "Массив не найден.\n";
        return;
    }

    std::vector<int> nums;
    for (int i = 0; i < arr->size; ++i) {
        try {
            nums.push_back(std::stoi(arr->data[i]));
        } catch (...) {
            // игнор
        }
    }

    if (nums.empty()) {
        std::cout << "Нет чисел в массиве.\n";
        return;
    }

    int target;
    std::cout << "Введите целевую сумму: ";
    std::cin >> target;

    std::unordered_map<int, int> prefix_sum_map;
    prefix_sum_map[0] = -1; // для подмассива с начала
    int current_sum = 0;
    bool found = false;

    for (int i = 0; i < nums.size(); ++i) {
        current_sum += nums[i];

        if (prefix_sum_map.find(current_sum - target) != prefix_sum_map.end()) {
            int start = prefix_sum_map[current_sum - target] + 1;
            int end = i;
            std::cout << "Найден подмассив с индекса " << start << " до " << end << ": ";
            for (int j = start; j <= end; ++j) {
                std::cout << nums[j] << " ";
            }
            std::cout << std::endl;
            found = true;
            break; // ищем первый
        }

        prefix_sum_map[current_sum] = i;
    }

    if (!found) {
        std::cout << "Подмассив с такой суммой не найден.\n";
    }
}