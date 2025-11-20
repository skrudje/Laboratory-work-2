// tasks/task62_restructure.cpp
#include "task62_restructure.hpp"
#include "../storage/storage.hpp"
#include <iostream>
#include <string>

void task62_run() {
    std::string table_name;
    std::cout << "Введите имя хеш-таблицы для реструктуризации: ";
    std::cin >> table_name;

    // Поиск таблицы с цепочками (из задания 2)
    Set* s = g_sets[table_name];
    if (!s) {
        std::cout << "Хеш-таблица '" << table_name << "' не найдена.\n";
        return;
    }

    double load_factor = static_cast<double>(s->count) / s->capacity;
    if (load_factor <= 0.9) {
        std::cout << "Хеш-таблица '" << table_name << "' заполнена на " << load_factor * 100 << "% (менее 90%). Реструктуризация не требуется.\n";
        return;
    }

    int new_capacity = s->capacity * 2;
    Set* new_set = set_create();
    new_set->capacity = new_capacity;
    new_set->buckets = new SetNode*[new_capacity]();

    // Перенос всех элементов с повторным хешированием
    for (int i = 0; i < s->capacity; ++i) {
        SetNode* node = s->buckets[i];
        while (node) {
            std::string key = node->key;
            unsigned int index = set_hash(key, new_capacity);
            SetNode* newNode = new SetNode(key);
            newNode->next = new_set->buckets[index];
            new_set->buckets[index] = newNode;
            new_set->count++;
            node = node->next;
        }
    }

    // Замена старой таблицы на новую
    set_free(s);
    g_sets[table_name] = new_set;

    std::cout << "Хеш-таблица '" << table_name << "' успешно реструктурирована. Новый размер: " << new_capacity << "\n";
}