// structures/  
#include "set.h"
#include <vector>

const int SET_INITIAL_CAPACITY = 16;

unsigned int set_hash(const std::string& key, int capacity) {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

Set* set_create() {
    Set* s = new Set;
    s->capacity = SET_INITIAL_CAPACITY;
    s->count = 0;
    s->buckets = new SetNode*[s->capacity]();
    return s;
}

bool set_add(Set* s, const std::string& key) {
    if (set_has(s, key)) return false;

    unsigned int index = set_hash(key, s->capacity);
    SetNode* newNode = new SetNode(key);
    newNode->next = s->buckets[index];
    s->buckets[index] = newNode;
    s->count++;
    return true;
}

bool set_del(Set* s, const std::string& key) {
    unsigned int index = set_hash(key, s->capacity);
    SetNode* node = s->buckets[index];
    SetNode* prev = nullptr;

    while (node) {
        if (node->key == key) {
            if (prev) {
                prev->next = node->next;
            } else {
                s->buckets[index] = node->next;
            }
            delete node;
            s->count--;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

bool set_has(Set* s, const std::string& key) {
    unsigned int index = set_hash(key, s->capacity);
    SetNode* node = s->buckets[index];
    while (node) {
        if (node->key == key) return true;
        node = node->next;
    }
    return false;
}

int set_size(Set* s) {
    return s ? s->count : 0;
}

// возвращает все элементы множества
std::vector<std::string> set_elements(Set* s) {
    std::vector<std::string> elems;
    for (int i = 0; i < s->capacity; ++i) {
        SetNode* node = s->buckets[i];
        while (node) {
            elems.push_back(node->key);
            node = node->next;
        }
    }
    return elems;
}

void set_free(Set* s) {
    for (int i = 0; i < s->capacity; ++i) {
        SetNode* node = s->buckets[i];
        while (node) {
            SetNode* next = node->next;
            delete node;
            node = next;
        }
    }
    delete[] s->buckets;
    delete s;
}