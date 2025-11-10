// structures/array.cpp
#include "array.h"
#include <iostream>
#include <stdexcept>

Array* array_create() {
    Array* arr = new Array;
    arr->data = nullptr;
    arr->size = 0;
    return arr;
}

void array_push_back(Array* arr, const std::string& value) {
    if (!arr) return;
    std::string* new_data = new std::string[arr->size + 1];
    for (int i = 0; i < arr->size; ++i) {
        new_data[i] = arr->data[i];
    }
    new_data[arr->size] = value;
    delete[] arr->data;
    arr->data = new_data;
    arr->size++;
}

void array_insert_at(Array* arr, int index, const std::string& value) {
    if (!arr || index < 0 || index > arr->size) return;
    std::string* new_data = new std::string[arr->size + 1];
    for (int i = 0; i < index; ++i) {
        new_data[i] = arr->data[i];
    }
    new_data[index] = value;
    for (int i = index; i < arr->size; ++i) {
        new_data[i + 1] = arr->data[i];
    }
    delete[] arr->data;
    arr->data = new_data;
    arr->size++;
}

std::string array_get(Array* arr, int index) {
    if (!arr || index < 0 || index >= arr->size) {
        throw std::out_of_range("The index is out of range");
    }
    return arr->data[index];
}

void array_set(Array* arr, int index, const std::string& value) {
    if (!arr || index < 0 || index >= arr->size) return;
    arr->data[index] = value;
}

void array_delete_at(Array* arr, int index) {
    if (!arr || index < 0 || index >= arr->size) return;
    if (arr->size == 1) {
        delete[] arr->data;
        arr->data = nullptr;
        arr->size = 0;
        return;
    }
    std::string* new_data = new std::string[arr->size - 1];
    for (int i = 0, j = 0; i < arr->size; ++i) {
        if (i == index) continue;
        new_data[j++] = arr->data[i];
    }
    delete[] arr->data;
    arr->data = new_data;
    arr->size--;
}

int array_size(Array* arr) {
    if (!arr) return 0;
    return arr->size;
}

void array_print(Array* arr) {
    if (!arr) {
        std::cout << "Array is null." << std::endl;
        return;
    }
    for (int i = 0; i < arr->size; ++i) {
        std::cout << "[" << i << "] " << arr->data[i] << std::endl;
    }
}

void array_free(Array* arr) {
    if (!arr) return;
    delete[] arr->data;
    delete arr;
}