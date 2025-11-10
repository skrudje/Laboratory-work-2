// structures/hash_table_cuckoo.h
#ifndef HASH_TABLE_CUCKOO_H
#define HASH_TABLE_CUCKOO_H

#include <string>

struct HashTableCuckoo {
    std::string* keys1;
    std::string* values1;
    std::string* keys2;
    std::string* values2;
    bool* occupied1;
    bool* occupied2;
    int capacity;
    int count;
    double load_factor_threshold;
};

HashTableCuckoo* ht_create(int initial_capacity);
bool ht_insert(HashTableCuckoo* ht, const std::string& key, const std::string& value);
bool ht_get(HashTableCuckoo* ht, const std::string& key, std::string& value);
bool ht_delete(HashTableCuckoo* ht, const std::string& key);
int ht_size(HashTableCuckoo* ht);
void ht_free(HashTableCuckoo* ht);

#endif // HASH_TABLE_CUCKOO_H