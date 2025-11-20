// structures/hash_table_double.cpp
#include "hash_table_double.h"
#include <iostream>
#include <stdexcept>

inline unsigned int hash1(const std::string& key, int capacity) {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

inline unsigned int hash2(const std::string& key, int capacity) {
    unsigned long hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % (capacity - 1);
    }
    return hash + 1;
}

HashTableDouble* ht_create_double(int initial_capacity) {
    HashTableDouble* ht = new HashTableDouble;
    ht->capacity = initial_capacity;
    ht->count = 0;
    ht->load_factor_threshold = 0.9;
    ht->keys = new std::string[ht->capacity];
    ht->values = new std::string[ht->capacity];
    ht->occupied = new bool[ht->capacity]();
    return ht;
}

bool ht_insert(HashTableDouble* ht, const std::string& key, const std::string& value) {
    if (!ht) return false;

    // Реструктуризация при заполнении > 90%
    if (static_cast<double>(ht->count) / ht->capacity > ht->load_factor_threshold) {
        int new_capacity = ht->capacity * 2;
        std::string* new_keys = new std::string[new_capacity];
        std::string* new_values = new std::string[new_capacity];
        bool* new_occupied = new bool[new_capacity]();

        // Перенос элементов
        for (int i = 0; i < ht->capacity; ++i) {
            if (ht->occupied[i]) {
                unsigned int h1 = hash1(ht->keys[i], new_capacity);
                unsigned int h2 = hash2(ht->keys[i], new_capacity);
                int j = 0;
                while (new_occupied[(h1 + j * h2) % new_capacity]) {
                    j++;
                }
                int index = (h1 + j * h2) % new_capacity;
                new_keys[index] = ht->keys[i];
                new_values[index] = ht->values[i];
                new_occupied[index] = true;
            }
        }

        delete[] ht->keys;
        delete[] ht->values;
        delete[] ht->occupied;
        ht->keys = new_keys;
        ht->values = new_values;
        ht->occupied = new_occupied;
        ht->capacity = new_capacity;
    }

    unsigned int h1 = hash1(key, ht->capacity);
    unsigned int h2 = hash2(key, ht->capacity);
    int j = 0;

    while (ht->occupied[(h1 + j * h2) % ht->capacity]) {
        if (ht->keys[(h1 + j * h2) % ht->capacity] == key) {
            ht->values[(h1 + j * h2) % ht->capacity] = value;
            return true;
        }
        j++;
    }

    int index = (h1 + j * h2) % ht->capacity;
    ht->keys[index] = key;
    ht->values[index] = value;
    ht->occupied[index] = true;
    ht->count++;
    return true;
}

bool ht_get(HashTableDouble* ht, const std::string& key, std::string& value) {
    if (!ht) return false;
    unsigned int h1 = hash1(key, ht->capacity);
    unsigned int h2 = hash2(key, ht->capacity);
    int j = 0;

    while (ht->occupied[(h1 + j * h2) % ht->capacity]) {
        if (ht->keys[(h1 + j * h2) % ht->capacity] == key) {
            value = ht->values[(h1 + j * h2) % ht->capacity];
            return true;
        }
        j++;
    }
    return false;
}

bool ht_delete(HashTableDouble* ht, const std::string& key) {
    if (!ht) return false;
    unsigned int h1 = hash1(key, ht->capacity);
    unsigned int h2 = hash2(key, ht->capacity);
    int j = 0;

    while (ht->occupied[(h1 + j * h2) % ht->capacity]) {
        if (ht->keys[(h1 + j * h2) % ht->capacity] == key) {
            ht->occupied[(h1 + j * h2) % ht->capacity] = false;
            ht->count--;
            return true;
        }
        j++;
    }
    return false;
}

int ht_size(HashTableDouble* ht) {
    return ht ? ht->count : 0;
}

void ht_free(HashTableDouble* ht) {
    if (!ht) return;
    delete[] ht->keys;
    delete[] ht->values;
    delete[] ht->occupied;
    delete ht;
}