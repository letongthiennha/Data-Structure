#include "HashTable.h"

HashTable::HashTable(int initsize)
    : table(initsize, HashTableCell(EMPTY)), current(0), size(initsize), hashPrime(7) {
    float initX = startX;
    float initY = 100;
    for (int i = 0; i < size; i++) {
        table[i].setPosition({initX, initY}); // Set both position and targetPosition
        if (size <= 10) {
            initX += (endX - startX) / size; // Distribute evenly for <= 10 cells
        } else {
            initX += (endX - startX) / 10;   // Distribute evenly for 10 cells per line
        }
        if ((i + 1) % 10 == 0) {
            initX = startX;  // Reset X position to the start
            initY += 100;    // Move down by 100 pixels
        }
    }
}

HashTable::~HashTable() {
    table.clear();
    current = 0;
    size = 0;
}

int HashTable::getSize() {
    return size;
}

int HashTable::getCurrent() {
    return current;
}

bool HashTable::isFull() {
    if (current == size) return true;
    return false;
}

bool HashTable::isEmpty() {
    if (size == 0) return true;
    return false;
}

void HashTable::resize(int newSize) {
    //resetHighlights();
    std::vector<HashTableCell> oldTable = table;

    table.resize(newSize, HashTableCell(EMPTY));
    table.clear();
    if (newSize < current) current = size;
    size = newSize;
    hashPrime = findClosePrime();
    resized = true;

    for (const auto& cell : oldTable) {
        if (cell.val != EMPTY) {
            add(cell.val);
        }
    }
}

void HashTable::add(int value) {
    //resetHighlights();
    if (isFull()) return;
    int hash = (value % hashPrime + hashPrime) % size;
    while (table[hash].val != EMPTY) {
        //table[hash].setHighlight(0.2f);
        if (table[hash].val == value) return;
        hash = (hash + 1) % size;
    }
    table[hash].val = value;
    current++;
}

void HashTable::remove(int value) {
    //resetHighlights();
    if (isEmpty()) return;
    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash].val != value) {
        //table[hash].setHighlight(0.2f);
        hash = (hash + 1) % size;
        if (hash == originalHash) return;
    }
    table[hash].val = EMPTY;
    //table[hash].setPersistentHighlight();
    current--;
}

bool HashTable::search(int value) {
    //resetHighlights();
    if (isEmpty()) return NOT_FOUND;
    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash].val != value) {
        //table[hash].setHighlight(0.2f);
        hash = (hash + 1) % size;
        if (hash == originalHash) return NOT_FOUND;
    }
    //table[hash].setPersistentHighlight();
    return FOUND;
}

bool HashTable::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++) {
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
/* 
void HashTable::resetHighlights() {
    for (int i = 0; i < size; i++) {
        table[i].unHighlight();
    }
}
 */
void HashTable::update() {
    if (resized) {
        resized = false;
    }
    float deltaTime = GetFrameTime();
    float initX = startX;
    float initY = 100;
    for (int i = 0; i < size; i++) {
        table[i].setTargetPosition({initX , initY});
        if (size <= 10) initX += (endX-startX) / size;
        else initX += (endX-startX) / 10;
        if ((i+1)%10 == 0) {
            initX = startX;
            initY += 100;
        }
        table[i].update(deltaTime);
    }
}

void HashTable::render() {
    for (int i = 0; i < size; i++) {
        table[i].render();
    }
}