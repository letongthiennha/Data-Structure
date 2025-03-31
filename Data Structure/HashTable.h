#pragma once

#include <vector>
#include <random>
#include "HashTableCell.h"
#include <queue>

const int NOT_FOUND = 0;
const int FOUND = 1;
const float startX = 350;
const float startY = 80;
const float endX = 1500;

class HashTable {
private:
    std::vector<HashTableCell> table;
    int current;
    int size;
    int hashPrime;

    std::queue<int> highlightQueue;
    std::queue<std::pair<int, int>> addQueue;
    std::queue<int> removeQueue;
    std::queue<int> findQueue;

    float highlightDuration = 0.3f; // Standard duration for highlighting
    bool highlightTask;

    float sequentialDuration = 0.05f; // Duration for sequential rendering
    bool sequentialRender;

public:
    HashTable(int initsize);
    ~HashTable();

    int getSize();
    int getCurrent();
    bool isFull();
    bool isEmpty();

    void randomTable();
    void resize(int newSize);
    void add(int value);
    int silentadd(int value);
    void remove(int value);
    bool search(int value);

    bool isPrime(int n);
    int findClosePrime(int x);

    void resetHighlights();
    void update();
    void render();
};