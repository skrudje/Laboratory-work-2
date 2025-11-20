// tasks/task1_logic.cpp
#include "task1_logic.hpp"
#include "../structures/stack.h"
#include <iostream>
#include <string>

int priority(const std::string& op) {
    if (op == "!") return 3;
    if (op == "&") return 2;
    if (op == "|" || op == "^") return 1;
    return 0;
}

std::string apply_op(const std::string& op, const std::string& b, const std::string& a = "") {
    int ib = (b == "1") ? 1 : 0;
    if (op == "!") return (ib == 0) ? "1" : "0";
    int ia = (a == "1") ? 1 : 0;
    if (op == "&") return (ia && ib) ? "1" : "0";
    if (op == "|") return (ia || ib) ? "1" : "0";
    if (op == "^") return (ia != ib) ? "1" : "0";
    return "0";
}

bool is_unary_not(const std::string& expr, size_t i) {
    if (expr[i] != '!') return false;
    if (i == 0) return true;
    char prev = expr[i - 1];
    return prev == '(' || prev == '!' || prev == '&' || prev == '|' || prev == '^';
}

std::string evaluate_logic_expression(const std::string& input_expr) {
    std::string expr;
    for (char c : input_expr) {
        if (c != ' ') expr += c;
    }

    Stack* vals = stack_create();
    Stack* ops = stack_create();

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        if (c == '0' || c == '1') {
            stack_push(vals, std::string(1, c));
        }
        else if (c == '(') {
            stack_push(ops, "(");
        }
        else if (c == ')') {
            while (!stack_empty(ops) && stack_peek(ops) != "(") {
                std::string op = stack_pop(ops);
                if (op == "!") {
                    std::string val = stack_pop(vals);
                    stack_push(vals, apply_op(op, val));
                } else {
                    std::string b = stack_pop(vals);
                    std::string a = stack_pop(vals);
                    stack_push(vals, apply_op(op, b, a));
                }
            }
            if (!stack_empty(ops)) stack_pop(ops);
        }
        else if (c == '!' || c == '&' || c == '|' || c == '^') {
            std::string op_str(1, c);
            if (c == '!' && is_unary_not(expr, i)) {
                stack_push(ops, op_str);
                continue;
            }
            while (!stack_empty(ops) && stack_peek(ops) != "(" &&
                   priority(stack_peek(ops)) >= priority(op_str)) {
                std::string op = stack_pop(ops);
                if (op == "!") {
                    std::string val = stack_pop(vals);
                    stack_push(vals, apply_op(op, val));
                } else {
                    std::string b = stack_pop(vals);
                    std::string a = stack_pop(vals);
                    stack_push(vals, apply_op(op, b, a));
                }
            }
            stack_push(ops, op_str);
        }
    }

    while (!stack_empty(ops)) {
        std::string op = stack_pop(ops);
        if (op == "!") {
            std::string val = stack_pop(vals);
            stack_push(vals, apply_op(op, val));
        } else {
            std::string b = stack_pop(vals);
            std::string a = stack_pop(vals);
            stack_push(vals, apply_op(op, b, a));
        }
    }

    std::string result = "0";
    if (!stack_empty(vals)) {
        result = stack_pop(vals);
    }

    stack_free(vals);
    stack_free(ops);
    return result;
}

void task1_run() {
    std::string expr;
    std::cout << "Введите логическое выражение (0, 1, !, &, |, ^, скобки): ";
    std::getline(std::cin >> std::ws, expr);
    std::cout << "Результат: \n" << evaluate_logic_expression(expr) << std::endl;
}