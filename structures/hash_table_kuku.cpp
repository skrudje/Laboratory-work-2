// structures/hash_table_kuku.cpp
#include "hash_table_kuku.h"
#include <iostream>
#include <stdexcept>

bool kuku_insert_step(HashTableKuku* ht, std::string& key, std::string& value, int max_attempts) {
    int table = 1; // начинаем с таблицы 1

    for (int attempt = 0; attempt < max_attempts; ++attempt) {
        if (table == 1) {
            unsigned int index = hash1(key, ht->capacity);
            if (!ht->occupied1[index]) {
                ht->keys1[index] = key;
                ht->values1[index] = value;
                ht->occupied1[index] = true;
                ht->count++;
                return true;
            } else {
                // Вытесняем
                std::string displaced_key = ht->keys1[index];
                std::string displaced_value = ht->values1[index];
                ht->keys1[index] = key;
                ht->values1[index] = value;
                key = displaced_key; // продолжаем с вытеснённым
                value = displaced_value;
                table = 2; // переключаемся на таблицу 2
            }
        } else { // table == 2
            unsigned int index = hash2(key, ht->capacity);
            if (!ht->occupied2[index]) {
                ht->keys2[index] = key;
                ht->values2[index] = value;
                ht->occupied2[index] = true;
                ht->count++;
                return true;
            } else {
                // Вытесняем
                std::string displaced_key = ht->keys2[index];
                std::string displaced_value = ht->values2[index];
                ht->keys2[index] = key;
                ht->values2[index] = value;
                key = displaced_key; // продолжаем с вытеснённым
                value = displaced_value;
                table = 1; // переключаемся на таблицу 1
            }
        }
    }
    return false; // не удалось вставить
}



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
        hash = (hash * 31 + c) % capacity;
    }
    return hash;
}

HashTableKuku* ht_create_kuku(int initial_capacity) {
    HashTableKuku* ht = new HashTableKuku;
    ht->capacity = initial_capacity;
    ht->count = 0;
    ht->load_factor_threshold = 0.9;
    ht->keys1 = new std::string[ht->capacity];
    ht->values1 = new std::string[ht->capacity];
    ht->keys2 = new std::string[ht->capacity];
    ht->values2 = new std::string[ht->capacity];
    ht->occupied1 = new bool[ht->capacity]();
    ht->occupied2 = new bool[ht->capacity]();
    return ht;
}

HashTableKuku* ht_create(int initial_capacity) {
    return ht_create_kuku(initial_capacity);
}

bool ht_insert(HashTableKuku* ht, const std::string& key, const std::string& value) {
    if (!ht) return false;

    // Реструктуризация при заполнении > 90%
    if (static_cast<double>(ht->count) / (2 * ht->capacity) > ht->load_factor_threshold) {
        int new_capacity = ht->capacity * 2;
        HashTableKuku* new_ht = ht_create(new_capacity);

        // Переносим все элементы
        for (int i = 0; i < ht->capacity; ++i) {
            if (ht->occupied1[i]) {
                ht_insert(new_ht, ht->keys1[i], ht->values1[i]);
            }
            if (ht->occupied2[i]) {
                ht_insert(new_ht, ht->keys2[i], ht->values2[i]);
            }
        }

        // Вставляем новый элемент
        if (ht_insert(new_ht, key, value)) {
            // Заменяем старую таблицу
            ht_free(ht);
            *ht = *new_ht;
            delete new_ht;
            return true;
        } else {
            ht_free(new_ht);
            return false;
        }
    }

    // Попытка вставить
    std::string k = key;
    std::string v = value;
    if (kuku_insert_step(ht, k, v)) {
        return true;
    }

    // Если не получилось — реструктуризация
    int new_capacity = ht->capacity * 2;
    HashTableKuku* new_ht = ht_create(new_capacity);

    // Переносим все элементы
    for (int i = 0; i < ht->capacity; ++i) {
        if (ht->occupied1[i]) {
            ht_insert(new_ht, ht->keys1[i], ht->values1[i]);
        }
        if (ht->occupied2[i]) {
            ht_insert(new_ht, ht->keys2[i], ht->values2[i]);
        }
    }

    // Вставляем новый элемент
    if (ht_insert(new_ht, key, value)) {
        // Заменяем старую таблицу
        ht_free(ht);
        *ht = *new_ht;
        delete new_ht;
        return true;
    }

    ht_free(new_ht);
    return false;
}

bool ht_get(HashTableKuku* ht, const std::string& key, std::string& value) {
    if (!ht) return false;
    unsigned int index1 = hash1(key, ht->capacity);
    if (ht->occupied1[index1] && ht->keys1[index1] == key) {
        value = ht->values1[index1];
        return true;
    }
    unsigned int index2 = hash2(key, ht->capacity);
    if (ht->occupied2[index2] && ht->keys2[index2] == key) {
        value = ht->values2[index2];
        return true;
    }
    return false;
}

bool ht_delete(HashTableKuku* ht, const std::string& key) {
    if (!ht) return false;
    unsigned int index1 = hash1(key, ht->capacity);
    if (ht->occupied1[index1] && ht->keys1[index1] == key) {
        ht->occupied1[index1] = false;
        ht->count--;
        return true;
    }
    unsigned int index2 = hash2(key, ht->capacity);
    if (ht->occupied2[index2] && ht->keys2[index2] == key) {
        ht->occupied2[index2] = false;
        ht->count--;
        return true;
    }
    return false;
}

int ht_size(HashTableKuku* ht) {
    return ht ? ht->count : 0;
}

void ht_free(HashTableKuku* ht) {
    if (!ht) return;
    delete[] ht->keys1;
    delete[] ht->values1;
    delete[] ht->keys2;
    delete[] ht->values2;
    delete[] ht->occupied1;
    delete[] ht->occupied2;
    delete ht;
}