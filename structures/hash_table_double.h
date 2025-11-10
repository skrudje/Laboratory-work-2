// structures/hash_table_double.h
#ifndef HASH_TABLE_DOUBLE_H
#define HASH_TABLE_DOUBLE_H

#include <string>

struct HashTableDouble {
    std::string* keys;
    std::string* values;
    bool* occupied;
    int capacity;
    int count;
    double load_factor_threshold;
};

HashTableDouble* ht_create(int initial_capacity = 16);
bool ht_insert(HashTableDouble* ht, const std::string& key, const std::string& value);
bool ht_get(HashTableDouble* ht, const std::string& key, std::string& value);
bool ht_delete(HashTableDouble* ht, const std::string& key);
int ht_size(HashTableDouble* ht);
void ht_free(HashTableDouble* ht);

#endif // HASH_TABLE_DOUBLE_H