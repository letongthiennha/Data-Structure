#pragma once

#include <string>

const std::string insertFront = {
    "ListNode* toInsert = new ListNode(val);\n"
    "toInsert.next = head;\n"
    "head = toInsert;"
};

const std::string popFront = {
    "ListNode* toDelete = head;\n"
    "head = head.next;\n"
    "delete toDelete;"
};

const std::string insertNode = {
    "ListNode* current = head;\n"
    "for (int i = 0; i < index - 1; i++) {\n"
    "    current = current.next;\n"
    "}\n"
    "ListNode* toInsert = new ListNode(value);\n"
    "toInsert.next = current.next;\n"
    "current.next = toInsert;"
};

const std::string removeNode = {
    "ListNode* current = head;\n"
    
    "ListNode* toDelete = current.next;\n"
    "current.next = current.next.next;\n"
    "delete toDelete;"
};

const std::string searchNode = {
    "ListNode* current = head;\n"
    "int index = 0;\n"
    "while (current != NULL) {\n"
    "    if (current.val == searchVal) return index;\n"
    "    current = current.next;\n"
    "    index++;\n"
    "}\n"
    "return -1;"
};

const std::string updateNode = {
    "ListNode* current = head;\n"
    "for (int i = 0; i < index; i++) {\n"
    "    current = current.next;\n"
    "}\n"
    "current.val = newValue;"
};
