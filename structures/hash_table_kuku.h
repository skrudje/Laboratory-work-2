// structures/hash_table_kuku.h
#ifndef HASH_TABLE_KUKU_H
#define HASH_TABLE_KUKU_H

#include <string>

struct HashTableKuku {
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

unsigned int hash1(const std::string& key, int capacity);
unsigned int hash2(const std::string& key, int capacity);

bool kuku_insert_step(HashTableKuku* ht, std::string& key, std::string& value, int max_attempts = 500);

HashTableKuku* ht_create(int initial_capacity = 16); 
HashTableKuku* ht_create_kuku(int initial_capacity = 16);

bool ht_insert(HashTableKuku* ht, const std::string& key, const std::string& value);
bool ht_get(HashTableKuku* ht, const std::string& key, std::string& value);
bool ht_delete(HashTableKuku* ht, const std::string& key);
int ht_size(HashTableKuku* ht);
void ht_free(HashTableKuku* ht);

#endif // HASH_TABLE_KUKU_H