// tasks/task3_partition.cpp
#include "task3_partition.hpp"
#include "../storage/storage.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

void task3_run() {
    std::string setname;
    std::cout << "Введите имя множества: ";
    std::cin >> setname;

    Set* s = g_sets[setname];
    if (!s) {
        std::cout << "АТД Множество не задано, вернитесь во 2 задание и укажите его.\n";
        return;
    }

    auto elems = set_elements(s);
    if (elems.empty()) {
        std::cout << "Пустое множество.\n";
        return;
    }

    // Преобразуем элементы в числа
    std::vector<int> nums;
    for (const auto& s : elems) {
        try {
            nums.push_back(std::stoi(s));
        } catch (...) {
            // игнорируем нечисловые
        }
    }

    if (nums.empty()) {
        std::cout << "Нет чисел в множестве.\n";
        return;
    }

    int total_sum = 0;
    for (int x : nums) total_sum += x;
    int target = total_sum / 2;

    // dp[i] = true, если можно получить сумму i
    std::vector<bool> dp(target + 1, false);
    dp[0] = true;

    std::vector<std::vector<int>> parent(target + 1);

    for (size_t idx = 0; idx < nums.size(); ++idx) {
        int num = nums[idx];
        for (int j = target; j >= num; --j) {
            if (dp[j - num] && !dp[j]) {
                dp[j] = true;
                parent[j] = parent[j - num];
                parent[j].push_back(static_cast<int>(idx));
            }
        }
    }

    int best = 0;
    for (int i = target; i >= 0; --i) {
        if (dp[i]) { best = i; break; }
    }

    std::vector<int> subset1;
    for (int idx : parent[best]) {
        subset1.push_back(nums[idx]);
    }

    std::vector<int> subset2;
    for (int x : nums) {
        auto it = std::find(subset1.begin(), subset1.end(), x);
        if (it == subset1.end()) {
            subset2.push_back(x);
        }
    }

    std::cout << "Подмножество 1: ";
    for (int x : subset1) std::cout << x << " ";
    std::cout << "\nСумма: " << best << std::endl;

    std::cout << "Подмножество 2: ";
    for (int x : subset2) std::cout << x << " ";
    std::cout << "\nСумма: " << (total_sum - best) << std::endl;

    std::cout << "Разница: " << std::abs((total_sum - best) - best) << "\n" << std::endl;
}