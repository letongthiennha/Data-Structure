#include "HashTable.h"

HashTable::HashTable(int initsize): table(initsize, EMPTY), current(0), size(initsize), hashPrime(7) {}

HashTable::~HashTable() {
    table.clear();
    current = 0;
    size = 0;
    hashPrime = 7;
}

int HashTable::getSize() {
    return size;
}

int HashTable::getCurrent() {
    return current;
}

bool HashTable::isFull() {
    if (current == size) return true;
}

bool HashTable::isEmpty() {
    if (size == 0) return true;
}

void HashTable::resize(int newSize) {
    table.resize(newSize, EMPTY);
    if (newSize < current) current = size; 
    size = newSize;
    hashPrime = findClosePrime();
}

void HashTable::add(int value) {
    if (isFull()) return;
    int hash = (value % hashPrime + hashPrime) % size;
    while (table[hash] != EMPTY) {
        if (table[hash] == value) return;
        hash = (hash + 1) % size;
    }
    table[hash] = value;
    current++;
}

void HashTable::remove(int value) {
    if (isEmpty()) return;
    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash] != value) {
        hash = (hash + 1) % size;
        if (hash == originalHash) return;
    }
    table[hash] = EMPTY;
    current--;
}

bool HashTable::search(int value) {
    if (isEmpty()) return NOT_FOUND;
    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash] != value) {
        hash = (hash + 1) % size;
        if (hash == originalHash) return NOT_FOUND;
    }
    return FOUND;
}

bool HashTable::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= std::sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int HashTable::findClosePrime() {
    if (size <= 23) return 7;
    for (int i = size; i > 1; i--) {
        if (isPrime(i)) return i;
    }
    return hashPrime; 
}