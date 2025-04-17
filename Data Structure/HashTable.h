#pragma once

#include <vector>
#include <random>
#include <queue>
#include <sstream>
#include "HashTableCell.h"
#include "Font.h"
const int NOT_FOUND = 0;
const int FOUND = 1;
const float startX = 350;
const float startY = 80;
const float endX = 1500;
const float defaultHighlightDuration = 0.3f;
const float defaultSequentialDuration = 0.05f;

enum AnimationState { IDLESTATE, PLAYING, PAUSED, FINALIZE };
struct Action {
    enum ActionType { ADD, REMOVE, RANDOMIZE, RESIZE, SEARCH } type;
    int index;      // Index in the hash table
    int value;      // Value involved in the action
    int prevValue;  // Previous value at the index (for undo/redo purposes)
    std::vector<int> tableValues; // State of the hash table at the time of the action
};
class HashTable {
private:
    std::vector<HashTableCell> table;
    int current;
    int size;
    int hashPrime;
    
    AnimationState animationState;
    std::deque<Action> actionHistory;
    std::deque<Action> redoStack;

    std::queue<int> highlightQueue;
    std::queue<std::pair<int, int>> addQueue;
    std::queue<int> removeQueue;
    std::queue<int> findQueue;

    float highlightDuration;
    bool highlightTask;
    int highlightedIndex;
    int displayHash;
    int displayValue;

    float sequentialDuration;
    bool sequentialRender;

public:
    HashTable(int initsize);
    ~HashTable();

    int getSize();
    int getCurrent();
    bool isFull();
    bool isEmpty();

    void setAnimationState(AnimationState state);
    AnimationState getAnimationState();
    void clearRedo();
    void clearHistory();
    void undo();
    void redo();
    bool canUndo();
    bool canRedo();

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