// structures/lfu_cache.h
#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <string>
#include <unordered_map>

struct LFUDataNode {
    std::string key;
    std::string value;
    int freq;
    LFUDataNode* prev;
    LFUDataNode* next;
};

struct LFUFreqList {
    int freq;
    LFUDataNode* head;
    LFUDataNode* tail;
    LFUFreqList* prev_list;
    LFUFreqList* next_list;
};

struct LFUCache {
    int capacity;
    LFUFreqList* min_freq_list;
    LFUFreqList* freq_lists_head;
    LFUFreqList* freq_lists_tail;

    std::unordered_map<std::string, LFUDataNode*> key_map;
};

LFUCache* lfu_create(int capacity);
void lfu_set(LFUCache* cache, const std::string& key, const std::string& value);
std::string lfu_get(LFUCache* cache, const std::string& key);
void lfu_free(LFUCache* cache);


#endif // LFU_CACHE_H