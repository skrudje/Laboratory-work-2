// tasks/task6_hash_test.cpp
#include "task6_hash_test.hpp"
#include <iostream>
#include <string>
#include <random>
#include <chrono>

// Копируем реализации хеш-таблиц сюда или подключаем
// Пока оставим заглушку

std::string generate_random_string(int len) {
    static const char alphanum[] = "0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    std::string s;
    for (int i = 0; i < len; ++i) {
        s += alphanum[dis(gen)];
    }
    return s;
}

void task6_run() {
    int N, M;
    std::cout << "Введите N (вставки): ";
    std::cin >> N;
    std::cout << "Введите M (поиски): ";
    std::cin >> M;

    std::cout << "Запуск эмпирического анализа (заглушка)...\n";

    auto start = std::chrono::high_resolution_clock::now();

    // Вставка N элементов
    for (int i = 0; i < N; ++i) {
        std::string key = generate_random_string(8);
        // вставить в хеш-таблицу
    }

    // Поиск M элементов
    for (int i = 0; i < M; ++i) {
        std::string key = generate_random_string(8);
        // найти в хеш-таблице
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Время выполнения: " << duration << " мкс\n";
}