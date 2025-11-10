// structures/lfu_cache.cpp
#include "lfu_cache.h"
#include <unordered_map>
#include <iostream>

// Глобальная карта для быстрого доступа к узлам по ключу
static std::unordered_map<std::string, LFUDataNode*> lfu_key_map;

// Вспомогательные функции для работы со списками частот
static LFUFreqList* create_freq_list(int freq) {
    LFUFreqList* list = new LFUFreqList;
    list->freq = freq;
    list->head = nullptr;
    list->tail = nullptr;
    list->prev_list = nullptr;
    list->next_list = nullptr;
    return list;
}

static void delete_freq_list(LFUFreqList* list) {
    LFUDataNode* current = list->head;
    while (current) {
        LFUDataNode* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

static void remove_node_from_freq_list(LFUCache* cache, LFUDataNode* node) {
    LFUFreqList* list = nullptr;
    LFUFreqList* current_list = cache->freq_lists_head;
    while (current_list) {
        if (current_list->freq == node->freq) {
            list = current_list;
            break;
        }
        current_list = current_list->next_list;
    }

    if (!list) return;

    if (list->head == list->tail) { // один узел
        if (cache->min_freq_list == list) {
            cache->min_freq_list = list->next_list;
        }
        if (list->prev_list) list->prev_list->next_list = list->next_list;
        if (list->next_list) list->next_list->prev_list = list->prev_list;
        if (cache->freq_lists_head == list) cache->freq_lists_head = list->next_list;
        if (cache->freq_lists_tail == list) cache->freq_lists_tail = list->prev_list;
        delete_freq_list(list);
    } else {
        if (list->head == node) {
            list->head = node->next;
            list->head->prev = nullptr;
        } else if (list->tail == node) {
            list->tail = node->prev;
            list->tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
}

static void add_node_to_freq_list(LFUCache* cache, LFUDataNode* node) {
    LFUFreqList* list = nullptr;
    LFUFreqList* current_list = cache->freq_lists_head;
    while (current_list) {
        if (current_list->freq == node->freq) {
            list = current_list;
            break;
        }
        current_list = current_list->next_list;
    }

    if (!list) {
        list = create_freq_list(node->freq);
        // Вставить список в нужное место (по возрастанию freq)
        LFUFreqList* current = cache->freq_lists_head;
        LFUFreqList* prev = nullptr;
        while (current && current->freq < list->freq) {
            prev = current;
            current = current->next_list;
        }

        list->next_list = current;
        list->prev_list = prev;
        if (prev) prev->next_list = list;
        if (current) current->prev_list = list;

        if (!cache->freq_lists_head) cache->freq_lists_head = list;
        if (!current) cache->freq_lists_tail = list;

        if (cache->min_freq_list && cache->min_freq_list->freq > list->freq) {
            cache->min_freq_list = list;
        } else if (!cache->min_freq_list) {
            cache->min_freq_list = list;
        }
    }

    node->next = list->head;
    node->prev = nullptr;
    if (list->head) list->head->prev = node;
    list->head = node;
    if (!list->tail) list->tail = node;
}

LFUCache* lfu_create(int capacity) {
    LFUCache* cache = new LFUCache;
    cache->capacity = capacity;
    cache->min_freq_list = nullptr;
    cache->freq_lists_head = nullptr;
    cache->freq_lists_tail = nullptr;
    lfu_key_map.clear();
    return cache;
}

void lfu_set(LFUCache* cache, const std::string& key, const std::string& value) {
    if (cache->capacity <= 0) return;

    auto it = lfu_key_map.find(key);
    if (it != lfu_key_map.end()) {
        // Ключ уже существует
        LFUDataNode* node = it->second;
        node->value = value;
        node->freq++;

        // Удалить из старого списка
        remove_node_from_freq_list(cache, node);

        // Добавить в новый список с увеличенной частотой
        add_node_to_freq_list(cache, node);

        return;
    }

    // Новый ключ
    if (lfu_key_map.size() >= cache->capacity) {
        // Удаляем наименее часто используемый (и самый старый в этой частоте)
        LFUFreqList* min_list = cache->min_freq_list;
        if (!min_list) return;

        LFUDataNode* node_to_remove = min_list->tail; // самый старый в списке
        lfu_key_map.erase(node_to_remove->key);

        if (min_list->head == min_list->tail) { // один узел
            if (cache->min_freq_list == min_list) {
                cache->min_freq_list = min_list->next_list;
            }
            if (min_list->prev_list) min_list->prev_list->next_list = min_list->next_list;
            if (min_list->next_list) min_list->next_list->prev_list = min_list->prev_list;
            if (cache->freq_lists_head == min_list) cache->freq_lists_head = min_list->next_list;
            if (cache->freq_lists_tail == min_list) cache->freq_lists_tail = min_list->prev_list;
            delete_freq_list(min_list);
        } else {
            min_list->tail = node_to_remove->prev;
            min_list->tail->next = nullptr;
            delete node_to_remove;
        }
    }

    // Создаём новый узел
    LFUDataNode* new_node = new LFUDataNode;
    new_node->key = key;
    new_node->value = value;
    new_node->freq = 1;
    new_node->prev = nullptr;
    new_node->next = nullptr;

    lfu_key_map[key] = new_node;

    // Добавляем в список частоты 1
    add_node_to_freq_list(cache, new_node);

    // Обновляем min_freq_list
    if (!cache->min_freq_list || cache->min_freq_list->freq > 1) {
        LFUFreqList* current = cache->freq_lists_head;
        while (current) {
            if (current->freq == 1) {
                cache->min_freq_list = current;
                break;
            }
            current = current->next_list;
        }
    }
}

std::string lfu_get(LFUCache* cache, const std::string& key) {
    auto it = lfu_key_map.find(key);
    if (it == lfu_key_map.end()) {
        return "-1";
    }

    LFUDataNode* node = it->second;
    std::string value = node->value;

    // Увеличиваем частоту
    node->freq++;

    // Удаляем из старого списка
    remove_node_from_freq_list(cache, node);

    // Добавляем в новый список
    add_node_to_freq_list(cache, node);

    // Обновляем min_freq_list, если нужно
    if (cache->min_freq_list && cache->min_freq_list->freq > node->freq) {
        LFUFreqList* current = cache->freq_lists_head;
        while (current) {
            if (current->freq == node->freq) {
                cache->min_freq_list = current;
                break;
            }
            current = current->next_list;
        }
    }

    return value;
}

void lfu_free(LFUCache* cache) {
    if (!cache) return;

    LFUFreqList* current = cache->freq_lists_head;
    while (current) {
        LFUFreqList* next = current->next_list;
        delete_freq_list(current);
        current = next;
    }

    lfu_key_map.clear();
    delete cache;
}