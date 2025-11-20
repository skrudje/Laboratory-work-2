// tasks/task5_huffman.cpp
#include "task5_huffman.hpp"
#include <iostream>
#include <string>

struct HNode {
    char symbol;
    int freq;
    HNode* left;
    HNode* right;
    HNode(char s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
};

// Мин-куча

struct MinHeap {
    HNode** data;
    int size;
    int capacity;

    MinHeap(int cap) : size(0), capacity(cap) {
        data = new HNode*[cap];
    }

    ~MinHeap() {
        for (int i = 0; i < size; ++i) {
            delete data[i];
        }
        delete[] data;
    }

    void push(HNode* node) {
        if (size >= capacity) return;
        data[size] = node;
        int i = size++;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (data[parent]->freq <= data[i]->freq) break;

            
            HNode* temp = data[parent];
            data[parent] = data[i];
            data[i] = temp;

            i = parent;
        }
    }

    HNode* pop() {
        if (size <= 0) return nullptr;
        HNode* root = data[0];
        data[0] = data[--size];
        heapify(0);
        return root;
    }

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && data[left]->freq < data[smallest]->freq) {
            smallest = left;
        }
        if (right < size && data[right]->freq < data[smallest]->freq) {
            smallest = right;
        }

        if (smallest != i) {
            
            HNode* temp = data[i];
            data[i] = data[smallest];
            data[smallest] = temp;

            heapify(smallest);
        }
    }

    bool empty() const {
        return size == 0;
    }
};

// функция для генерации кодов
void generate_codes(HNode* node, const std::string& code, std::string* code_map, char* symbols, int* symbol_count) {
    if (!node) return;
    if (!node->left && !node->right) {
        // Сохраняем код в массиве
        code_map[node->symbol] = code;
        symbols[*symbol_count] = node->symbol;
        (*symbol_count)++;
    }
    generate_codes(node->left, code + "0", code_map, symbols, symbol_count);
    generate_codes(node->right, code + "1", code_map, symbols, symbol_count);
}

void task5_run() {
    std::string text;
    std::cout << "Введите строку для кодирования: ";
    std::getline(std::cin >> std::ws, text);

    // Подсчёт частот вручную
    struct FreqEntry {
        char c;
        int freq;
    };
    FreqEntry freq_map[256]; // для ASCII
    int freq_count = 0;

    for (char c : text) {
        bool found = false;
        for (int i = 0; i < freq_count; ++i) {
            if (freq_map[i].c == c) {
                freq_map[i].freq++;
                found = true;
                break;
            }
        }
        if (!found) {
            freq_map[freq_count++] = {c, 1};
        }
    }

    // Создаём мин-кучу
    MinHeap heap(freq_count);
    for (int i = 0; i < freq_count; ++i) {
        heap.push(new HNode(freq_map[i].c, freq_map[i].freq));
    }

    // Построение дерева
    while (heap.size > 1) {
        HNode* left = heap.pop();
        HNode* right = heap.pop();
        HNode* parent = new HNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        heap.push(parent);
    }

    HNode* root = heap.pop();

    // Генерация кодов
    std::string code_map[256];
    char symbols[256];
    int symbol_count = 0;
    generate_codes(root, "", code_map, symbols, &symbol_count);

    // Вывод таблицы
    std::cout << "Таблица кодов:\n";
    for (int i = 0; i < symbol_count; ++i) {
        char c = symbols[i];
        std::cout << c << " -> " << code_map[c] << std::endl;
    }

    // Кодирование
    std::string encoded;
    for (char c : text) {
        encoded += code_map[c];
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
    std::cout << "Декодированная строка: \n" << decoded << std::endl;

    delete root;
}