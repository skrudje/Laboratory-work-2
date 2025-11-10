// structures/array.h
#pragma once

#include <string>

struct Array {
    std::string* data;
    int size;
};

// Создание пустого массива
Array* array_create();

// Добавление в конец
void array_push_back(Array* arr, const std::string& value);

// Вставка по индексу (0 <= index <= size)
void array_insert_at(Array* arr, int index, const std::string& value);

// Получение элемента по индексу
std::string array_get(Array* arr, int index);

// Замена элемента по индексу
void array_set(Array* arr, int index, const std::string& value);

// Удаление по индексу
void array_delete_at(Array* arr, int index);

// Размер массива
int array_size(Array* arr);

// Печать (чтение)
void array_print(Array* arr);

// Освобождение памяти
void array_free(Array* arr);