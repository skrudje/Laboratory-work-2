// storage/storage.hpp
#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <map>
#include "../structures/set.h"              
#include "../structures/array.h"            
#include "../structures/lfu_cache.h"        
#include "../structures/hash_table_double.h"
#include "../structures/hash_table_kuku.h" 

// Глобальные хранилища
extern std::map<std::string, Set*> g_sets;
extern std::map<std::string, Array*> g_arrays;
extern LFUCache* g_lfu;
extern std::map<std::string, HashTableDouble*> g_hash_tables_double;
extern std::map<std::string, HashTableKuku*> g_hash_tables_kuku;

void storage_load(const std::string& filename);
void storage_save(const std::string& filename);

Set* get_or_create_set(const std::string& name);
Array* get_or_create_array(const std::string& name);

#endif // STORAGE_HPP