// storage/storage.cpp
#include "storage.hpp"
#include "../nlohmann/json.hpp"
#include "../structures/hash_table_double.h"
#include "../structures/hash_table_kuku.h"
#include <fstream>

using json = nlohmann::json;

std::map<std::string, Set*> g_sets;
std::map<std::string, Array*> g_arrays;
LFUCache* g_lfu = nullptr;

std::map<std::string, HashTableDouble*> g_hash_tables_double;
std::map<std::string, HashTableKuku*> g_hash_tables_kuku;

void storage_load(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) return;

    json j;
    f >> j;
    f.close();

    if (j.contains("sets")) {
        for (auto& [name, arr] : j["sets"].items()) {
            Set* s = set_create();
            for (const auto& item : arr) {
                set_add(s, item.get<std::string>());
            }
            g_sets[name] = s;
        }
    }

    if (j.contains("arrays")) {
        for (auto& [name, arr] : j["arrays"].items()) {
            Array* a = array_create();
            for (const auto& item : arr) {
                array_push_back(a, item.get<std::string>());
            }
            g_arrays[name] = a;
        }
    }

        // Хеш-таблицы — если есть в файле
    if (j.contains("hash_tables_double")) {
        for (auto& [name, arr] : j["hash_tables_double"].items()) {
            HashTableDouble* ht = ht_create_double(16);
            // загрузка элементов
            g_hash_tables_double[name] = ht;
        }
    }

    if (j.contains("hash_tables_kuku")) {
        for (auto& [name, arr] : j["hash_tables_kuku"].items()) {
            HashTableKuku* ht = ht_create_kuku(16);
            // загрузка элементов
            g_hash_tables_kuku[name] = ht;
        }
    }
}



void storage_save(const std::string& filename) {
    json j;

    for (const auto& [name, s] : g_sets) {
        j["sets"][name] = set_elements(s);
    }

    for (const auto& [name, a] : g_arrays) {
        j["arrays"][name] = std::vector<std::string>(a->data, a->data + a->size);
    }

    // Сохранение хеш-таблицы
    for (const auto& [name, ht] : g_hash_tables_double) {
        // сохранение элементов
    }

    for (const auto& [name, ht] : g_hash_tables_kuku) {
        // сохранение элементов
    }

    std::ofstream f(filename);
    f << j.dump(4);
    f.close();
}

Set* get_or_create_set(const std::string& name) {
    if (g_sets.find(name) == g_sets.end()) {
        g_sets[name] = set_create();
    }
    return g_sets[name];
}

Array* get_or_create_array(const std::string& name) {
    if (g_arrays.find(name) == g_arrays.end()) {
        g_arrays[name] = array_create();
    }
    return g_arrays[name];
}