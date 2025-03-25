#pragma once

#include <string>

const std::string addKey = {
    "if (table.isFull) return;\n"
    "int hash = key % size;\n"
    "while (table[hash] != NULL) {\n"
    "    hash = (hash + 1) % size;\n"
    "}\n"
    "table[hash] = key;"
};  

const std::string deleteKey = {
    "if (table.isEmpty) return;\n"
    "int hash = key % size;\n"
    "int originalHash = hash;\n"
    "while (table[hash] != key) {\n"
    "    hash = (hash + 1) % size;\n"
    "    if (hash == originalHash) return;\n"
    "}\n"
    "table[hash] = NULL;"
};

const std::string searchKey = {
    "if (table.isEmpty) return NOT_FOUND;\n"
    "int hash = key % size;\n"
    "int originalHash = hash;\n"
    "while (table[hash] != key) {\n"
    "    hash = (hash + 1) % size;\n"
    "    if (hash == originalHash) return NOT_FOUND;\n"
    "}\n"
    "return FOUND;"
};