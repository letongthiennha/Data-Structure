#pragma once

#include <vector>
#include "HashTableCell.h"

const int NOT_FOUND = 0;
const int FOUND = 1;
const float startX = 200;
const float endX = 1400;
class HashTable {
private:
    std::vector<HashTableCell> table;
    int current;
    int size;
    int hashPrime;

    bool resized;

public:
    HashTable(int initsize);
    ~HashTable();

    int getSize();
    int getCurrent();
    bool isFull();
    bool isEmpty();

    void resize(int newSize);
    void add(int value);
    void remove(int value);
    bool search(int value);

    bool isPrime(int n);
    int findClosePrime();

    //void resetHighlights();
    void update();
    void render();
};