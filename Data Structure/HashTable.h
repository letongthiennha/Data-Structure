#pragma once

#include <vector>
#include <climits>
#include <cmath>

const int EMPTY = INT_MIN;
const int NOT_FOUND = 0;
const int FOUND = 1;

class HashTable {
private:
    std::vector<int> table;
    int current;
    int size;
    int hashPrime;
    
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
};