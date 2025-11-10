// structures/stack.cpp
#include "stack.h"

Stack* stack_create() {
    Stack* s = new Stack;
    s->top = nullptr;
    s->size = 0;
    return s;
}

bool stack_empty(Stack* s) {
    return s->top == nullptr;
}

void stack_push(Stack* s, const std::string& value) {
    SNode* node = new SNode{value, s->top};
    s->top = node;
    s->size++;
}

std::string stack_pop(Stack* s) {
    if (!s->top) throw std::runtime_error("Stack is empty");
    SNode* tmp = s->top;
    std::string val = tmp->data;
    s->top = s->top->next;
    delete tmp;
    s->size--;
    return val;
}

std::string stack_peek(Stack* s) {
    if (!s->top) throw std::runtime_error("Stack is empty");
    return s->top->data;
}

int stack_size(Stack* s) {
    return s->size;
}

void stack_print(Stack* s) {
    SNode* cur = s->top;
    int i = 0;
    while (cur) {
        // убираем std::cout, если не нужен вывод в final-версии
        // или оставляем — как в твоём stack.txt
        // std::cout << "[" << i++ << "] " << cur->data << std::endl;
        cur = cur->next;
    }
}

void stack_free(Stack* s) {
    while (s->top) {
        SNode* tmp = s->top;
        s->top = s->top->next;
        delete tmp;
    }
    delete s;
}