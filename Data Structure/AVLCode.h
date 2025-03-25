#pragma once

#include <string>

const std::string searchKey {
    "if NULL\n"
    "   return NOT_FOUND\n"
    "if key < value\n"
    "   searchLeft\n"
    "if key > value\n"
    "   searchRight"
};

const std::string insertKey {
    "Insert key\n"
    "Assess balance factor:\n"
    "   L-L case: rotateRight\n"
    "   R-R case: rotateLeft\n"
    "   L-R case: left.rotateleft; rotateRight\n"
    "   R-L case: right.rotateRight; rotateLeft\n"
};

const std::string deleteKey {
    "Delete key\n"
    "Assess balance factor:\n"
    "   L-L case: rotateRight\n"
    "   R-R case: rotateLeft\n"
    "   L-R case: left.rotateleft; rotateRight\n"
    "   R-L case: right.rotateRight; rotateLeft\n"
};
