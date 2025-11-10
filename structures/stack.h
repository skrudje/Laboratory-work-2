#pragma once

#include <string>
#include <stdexcept>

struct SNode {
    std::string data;
    SNode* next;
};

struct Stack {
    SNode* top;
    int size;
};

Stack* stack_create();
bool stack_empty(Stack* s);
void stack_push(Stack* s, const std::string& value);
std::string stack_pop(Stack* s);
std::string stack_peek(Stack* s);
int stack_size(Stack* s);
void stack_print(Stack* s);
void stack_free(Stack* s);
