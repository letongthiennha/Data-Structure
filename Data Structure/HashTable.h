#pragma once

#include <vector>
#include <random>
#include <queue>
#include "HashTableCell.h"

const int NOT_FOUND = 0;
const int FOUND = 1;
const float startX = 350;
const float startY = 80;
const float endX = 1500;
const float defaultHighlightDuration = 0.3f;
const float defaultSequentialDuration = 0.05f;

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

    float highlightDuration;
    bool highlightTask;

    float sequentialDuration;
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

    float coefficients[4] = {0.5, 1.0, 1.5, 2.0};
    int currentCoefficient;
    void setHighlightCoefficient(float coefficient);
    void setRenderCoefficient(float coefficient);

    bool isPrime(int n);
    int findClosePrime(int x);

    void resetHighlights();
    void update();
    void render();
};