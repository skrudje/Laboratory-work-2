// tasks/task5_huffman.cpp
#include "task5_huffman.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

struct HNode {
    char symbol;
    int freq;
    HNode* left;
    HNode* right;
    HNode(char s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HNode* a, HNode* b) {
        return a->freq > b->freq;
    }
};

void generate_codes(HNode* node, const std::string& code, std::unordered_map<char, std::string>& codes) {
    if (!node) return;
    if (!node->left && !node->right) {
        codes[node->symbol] = code;
    }
    generate_codes(node->left, code + "0", codes);
    generate_codes(node->right, code + "1", codes);
}

void free_tree(HNode* node) {
    if (node) {
        free_tree(node->left);
        free_tree(node->right);
        delete node;
    }
}

void task5_run() {
    std::string text;
    std::cout << "Введите строку для кодирования: ";
    std::getline(std::cin >> std::ws, text);

    std::map<char, int> freq;
    for (char c : text) freq[c]++;

    std::priority_queue<HNode*, std::vector<HNode*>, Compare> pq;
    for (auto& p : freq) {
        pq.push(new HNode(p.first, p.second));
    }

    while (pq.size() > 1) {
        HNode* left = pq.top(); pq.pop();
        HNode* right = pq.top(); pq.pop();
        HNode* parent = new HNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    HNode* root = pq.top();

    std::unordered_map<char, std::string> codes;
    generate_codes(root, "", codes);

    std::cout << "Таблица кодов:\n";
    for (auto& p : codes) {
        std::cout << p.first << " -> " << p.second << std::endl;
    }

    std::string encoded;
    for (char c : text) {
        encoded += codes[c];
    }
    std::cout << "Закодированная строка: " << encoded << std::endl;

    // Декодирование
    std::string decoded;
    HNode* current = root;
    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current && !current->left && !current->right) {
            decoded += current->symbol;
            current = root;
        }
    }
    std::cout << "Декодированная строка: " << decoded << std::endl;

    free_tree(root);
}