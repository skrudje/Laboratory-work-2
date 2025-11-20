// utils/set_cmd.cpp
#include "set_cmd.hpp"
#include <sstream>
#include <vector>
#include "../storage/storage.hpp"

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string execute_set_command(const std::string& query) {
    auto parts = split(query, ' ');
    if (parts.size() < 3) return "ERROR";

    std::string cmd = parts[0];
    std::string setname = parts[1];
    std::string value = parts[2];

    Set* s = get_or_create_set(setname);

    if (cmd == "SADD") {
        bool added = set_add(s, value);
        return added ? "TRUE" : "FALSE";
    }
    else if (cmd == "SETDEL") {
        bool removed = set_del(s, value);
        return removed ? "TRUE" : "FALSE";
    }
    else if (cmd == "SET_AT") {
        bool exists = set_has(s, value);
        return exists ? "TRUE" : "FALSE";
    }

    return "ERROR: unknown command";
}