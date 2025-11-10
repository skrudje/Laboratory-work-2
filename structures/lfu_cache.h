// structures/lfu_cache.hpp
#ifndef LFU_CACHE_HPP
#define LFU_CACHE_HPP

#include <string>

// Внутренняя структура узла данных
struct LFUDataNode {
    std::string key;
    std::string value;
    int freq;
    LFUDataNode* prev;
    LFUDataNode* next;
};

// Внутренняя структура списка узлов с одинаковой частотой
struct LFUFreqList {
    int freq;
    LFUDataNode* head;
    LFUDataNode* tail;
    LFUFreqList* prev_list;
    LFUFreqList* next_list;
};

// Основная структура LFU-кэша
struct LFUCache {
    int capacity;
    LFUFreqList* min_freq_list; // указатель на список с минимальной частотой
    LFUFreqList* freq_lists_head; // голова списка списков частот
    LFUFreqList* freq_lists_tail; // хвост списка списков частот
};

// Создание кэша
LFUCache* lfu_create(int capacity);

// Установка значения по ключу
void lfu_set(LFUCache* cache, const std::string& key, const std::string& value);

// Получение значения по ключу
std::string lfu_get(LFUCache* cache, const std::string& key);

// Удаление кэша
void lfu_free(LFUCache* cache);

#endif // LFU_CACHE_HPP