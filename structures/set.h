// structures/set.h
#ifndef SET_H
#define SET_H

#include <string>
#include <vector>

struct SetNode {
    std::string key;
    SetNode* next;
    SetNode(const std::string& k) : key(k), next(nullptr) {}
};

struct Set {
    SetNode** buckets;
    int capacity;
    int count;
};

Set* set_create();
bool set_add(Set* s, const std::string& key);
bool set_del(Set* s, const std::string& key);
bool set_has(Set* s, const std::string& key);
int set_size(Set* s);
std::vector<std::string> set_elements(Set* s); // нужно для JSON
void set_free(Set* s);

#endif // SET_H