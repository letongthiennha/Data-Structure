#include "HashTable.h"
#include <iostream>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> radsize(5, 70);
std::uniform_int_distribution<> radElement(-500, 500);

HashTable::HashTable(int initsize)
    : table(initsize, HashTableCell(EMPTY)), current(0), size(initsize), hashPrime(7), currentCoefficient(1) {
    highlightDuration = defaultHighlightDuration;
    sequentialDuration = defaultSequentialDuration;
    float initX = startX;
    float initY = startY;
    sequentialRender = true;
    for (int i = 0; i < size; i++) {
        table[i].index = i;
        table[i].setPosition({initX, initY}); 
        initX += (endX - startX) / 9;   
        if ((i + 1) % 10 == 0) {
            initX = startX;  
            initY += 100;    
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
void HashTable::randomTable() {
    int newSize = radsize(gen);
    int numberOfElements = radsize(gen) % newSize;
    HashTable newHashTable(newSize);
    newHashTable.hashPrime = findClosePrime(newSize);
    for (int i = 0; i < numberOfElements; i++) {
        int randomValue = radElement(gen);
        newHashTable.silentadd(randomValue);
    }

    table = std::move(newHashTable.table);
    size = newSize;
    current = newHashTable.getCurrent();
    hashPrime = newHashTable.hashPrime;
    sequentialRender = true;
}

void HashTable::resize(int newSize) {
    resetHighlights();
    if (newSize == 0) {
        table.clear();
        current = 0;
        size = 0;
        return;
    }
    std::vector<HashTableCell> oldTable = table;
    HashTable newHashTable(newSize);
    newHashTable.hashPrime = findClosePrime(newSize);
    for (int i = 0; i < oldTable.size(); i++) {
        if (oldTable[i].val != EMPTY) {
            newHashTable.silentadd(table[i].val);
        }
    }
    table = std::move(newHashTable.table);
    size = newSize;
    current = newHashTable.getCurrent();
    hashPrime = newHashTable.hashPrime;
    sequentialRender = true;
}
void HashTable::add(int value) {
    resetHighlights();
    if (isFull()) return;

    int hash = (value % hashPrime + hashPrime) % size;
    while (table[hash].val != EMPTY) {
        highlightQueue.push(hash); 
        if (table[hash].val == value) return;
        hash = (hash + 1) % size;
    }
    addQueue.push({hash, value});
    highlightQueue.push(hash);
    current++;
}

int HashTable::silentadd(int value) {
    if (isFull()) return -1;
    int hash = (value % hashPrime + hashPrime) % size;
    while (table[hash].val != EMPTY) {
        hash = (hash + 1) % size;
    }
    table[hash].val = value;
    current++;
    return hash;
}

void HashTable::remove(int value) {
    resetHighlights();
    if (isEmpty()) return;
    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash].val != value) {
        highlightQueue.push(hash);
        hash = (hash + 1) % size;
        if (hash == originalHash) return;
    }
    removeQueue.push(hash);
    highlightQueue.push(hash);
    current--;
}

bool HashTable::search(int value) {
    resetHighlights();
    if (isEmpty()) return NOT_FOUND;

    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash].val != value) {
        highlightQueue.push(hash); 
        hash = (hash + 1) % size;
        if (hash == originalHash) return NOT_FOUND;
    }
    highlightQueue.push(hash);
    findQueue.push(hash);
    return FOUND;
}

bool HashTable::isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int HashTable::findClosePrime(int x) {
    if (x <= 23) return 7;
    for (int i = x; i > 1; i--) {
        if (isPrime(i)) return i;
    }
    return x; 
}

 
void HashTable::resetHighlights() {
    for (int i = 0; i < size; i++) {
        table[i].unHighlight();
    }
}

void HashTable::setHighlightCoefficient(float coefficient) {
    highlightDuration = defaultHighlightDuration/coefficient;
}

void HashTable::setRenderCoefficient(float coefficient) {
    sequentialDuration = defaultSequentialDuration/coefficient;
}

void HashTable::update() {
    float deltaTime = GetFrameTime();

    static float highlightTimer = 0.0f; 
    highlightTimer -= deltaTime;

    if (!highlightQueue.empty() && highlightTimer <= 0.0f) {
        int index = highlightQueue.front();
        highlightQueue.pop();
        table[index].setHighlight(highlightDuration);
        highlightTimer = highlightDuration;
        highlightTask = true;
    }

    if (highlightTask && highlightTimer <= 0.0f) {
        highlightTask = false;
        if (!addQueue.empty()) {
            int index = addQueue.front().first;
            int value = addQueue.front().second;
            addQueue.pop();
            table[index].setValue(value);
        }
        if (!removeQueue.empty()) {
            int index = removeQueue.front();
            removeQueue.pop();
            table[index].setValue(EMPTY);
        }
        if (!findQueue.empty()) {
            int index = findQueue.front();
            findQueue.pop();
            table[index].setPersistentHighlight();
        }
    }

    for (int i = 0; i < size; i++) {
        table[i].update(deltaTime);
    }
}

void HashTable::render() {
    static int toRender = 0;
    static float renderTimer = sequentialDuration;
    float deltaTime = GetFrameTime();

    if (sequentialRender) {
        for (int i = 0; i < toRender; i++) {
            table[i].render();
        }
        renderTimer -= deltaTime;
        if (renderTimer <= 0.0f) { 
            if (toRender < size) {
                toRender++; 
                renderTimer = sequentialDuration; 
            } else {
                sequentialRender = false;
                toRender = 0;
            }
        }
    } else  {  
        for (int i = 0; i < size; i++) {
            table[i].render();
        }
    }
}