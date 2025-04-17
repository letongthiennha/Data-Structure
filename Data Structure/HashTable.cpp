#include "HashTable.h"
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> radsize(5, 70);
std::uniform_int_distribution<> radElement(-500, 500);

HashTable::HashTable(int initsize)
    : table(initsize, HashTableCell(EMPTY)), current(0), size(initsize), hashPrime(7), currentCoefficient(1) {
    animationState = IDLESTATE;
    highlightDuration = defaultHighlightDuration;
    sequentialDuration = defaultSequentialDuration;
    highlightedIndex = -1;
    displayHash = -1;
    displayValue = 0;
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
    std::vector<int> temp;
    for (int i = 0; i < size; i++) {
        temp.push_back(table[i].val);
    }
    actionHistory.push_back({Action::RANDOMIZE, current, size, hashPrime, temp});
    //clearRedo();
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

    animationState = PLAYING;
}

void HashTable::resize(int newSize) {
    resetHighlights();
    if (newSize == 0) {
        table.clear();
        current = 0;
        size = 0;
        return;
    }
    
    //std::vector<HashTableCell> oldTable = table;
    HashTable newHashTable(newSize);
    newHashTable.hashPrime = findClosePrime(newSize);

    std::vector<int> temp;
    for (int i = 0; i < size; i++) {
        temp.push_back(table[i].val);
        if (table[i].val != EMPTY) {
            newHashTable.silentadd(table[i].val);
        }
    }

    actionHistory.push_back({Action::RESIZE, current, size, hashPrime, temp});
    //clearRedo();

    table = std::move(newHashTable.table);
    size = newSize;
    current = newHashTable.getCurrent();
    hashPrime = newHashTable.hashPrime;
    sequentialRender = true;
    animationState = PLAYING;
}
void HashTable::add(int value) {
    resetHighlights();
    if (isFull()) return;
    animationState = PLAYING;
    int hash = (value % hashPrime + hashPrime) % size;
    while (table[hash].val != EMPTY) {
        highlightQueue.push(hash); 
        if (table[hash].val == value) return;
        hash = (hash + 1) % size;
    }
    actionHistory.push_back({Action::ADD, hash, value, table[hash].val});
    //clearRedo();
    addQueue.push({hash, value});
    displayValue = value;
    highlightQueue.push(hash);
    current++;
}

int HashTable::silentadd(int value) {
    if (isFull()) return -1;
    int hash = (value % hashPrime + hashPrime) % size;
    while (table[hash].val != EMPTY) {
        hash = (hash + 1) % size;
        if (table[hash].val == value) return -1;
    }
    table[hash].val = value;
    current++;
    return hash;
}

void HashTable::remove(int value) {
    resetHighlights();
    displayValue = value;
    if (isEmpty()) return;
    animationState = PLAYING;
    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash].val != value) {
        highlightQueue.push(hash);
        hash = (hash + 1) % size;
        if (hash == originalHash) return;
    }
    actionHistory.push_back({Action::REMOVE, hash, EMPTY, table[hash].val});
    //clearRedo();
    removeQueue.push(hash);
    highlightQueue.push(hash);
    current--;
}

bool HashTable::search(int value) {
    resetHighlights();
    displayValue = value;
    animationState = PLAYING;
    if (isEmpty()) return NOT_FOUND;

    int hash = (value % hashPrime + hashPrime) % size;
    int originalHash = hash;
    while (table[hash].val != value) {
        highlightQueue.push(hash); 
        hash = (hash + 1) % size;
        if (hash == originalHash) return NOT_FOUND;
    }
    actionHistory.push_back({Action::SEARCH, hash, value, table[hash].val});
    highlightQueue.push(hash);
    //clearRedo();
    findQueue.push(hash);
    return FOUND;
}

void HashTable::undo() {
    if (actionHistory.empty()) return;
    resetHighlights();
    Action lastAction = actionHistory.back();
    actionHistory.pop_back();

    switch (lastAction.type) {
        case Action::ADD:  
            table[lastAction.index].setValue(EMPTY);
            current--;
            redoStack.push_back(lastAction);
            break;
        case Action::REMOVE:
            table[lastAction.index].setValue(lastAction.prevValue);
            current++;
            redoStack.push_back(lastAction);
            break;
        case Action::SEARCH:
            table[lastAction.index].unHighlight();
            redoStack.push_back(lastAction);
            break;

        case Action::RANDOMIZE: {
            std::vector<int> temp;
            for (int i = 0; i < size; i++) {
                temp.push_back(table[i].val);
            }
            redoStack.push_back({Action::RANDOMIZE, current, size, hashPrime, temp});

            current = lastAction.index;
            size = lastAction.value;
            hashPrime = lastAction.prevValue;
            HashTable newHashTable(size);
            for (int i = 0; i < lastAction.tableValues.size(); i++) {
                newHashTable.table[i].setValue(lastAction.tableValues[i]);
            }
            table = newHashTable.table;
            sequentialRender = true;
            break;
        }
        case Action::RESIZE: {
            std::vector<int> temp;
            for (int i = 0; i < size; i++) {
                temp.push_back(table[i].val);
            }
            redoStack.push_back({Action::RESIZE, current, size, hashPrime, temp});

            current = lastAction.index;
            size = lastAction.value;
            hashPrime = lastAction.prevValue;
            HashTable newHashTable(size);
            for (int i = 0; i < lastAction.tableValues.size(); i++) {
                if (lastAction.tableValues[i] != EMPTY) {
                    newHashTable.table[i].setValue(lastAction.tableValues[i]);
                }
            }
            table = newHashTable.table;
            sequentialRender = true;
            break;
        }
        default: break;
    }
}

void HashTable::redo() {
    if (redoStack.empty()) return;
    resetHighlights();
    Action lastAction = redoStack.back();
    redoStack.pop_back();

    switch (lastAction.type) {
        case Action::ADD:
            add(lastAction.value);
            break;
        case Action::REMOVE:
            remove(lastAction.prevValue);
            break;
        case Action::SEARCH:
            search(lastAction.value);
            break;
        case Action::RANDOMIZE: {
            std::vector<int> temp;
            for (int i = 0; i < size; i++) {
                temp.push_back(table[i].val);
            }
            actionHistory.push_back({Action::RANDOMIZE, current, size, hashPrime, temp});

            current = lastAction.index;
            size = lastAction.value;
            hashPrime = lastAction.prevValue;
            HashTable newHashTable(size);
            for (int i = 0; i < lastAction.tableValues.size(); i++) {
                if (lastAction.tableValues[i] != EMPTY) {
                    newHashTable.table[i].setValue(lastAction.tableValues[i]);
                }
            }
            table = newHashTable.table;
            sequentialRender = true;
            break;
        }
        case Action::RESIZE: {
            resize(lastAction.value);
        }
        default: break;
    }
}

void HashTable::setAnimationState(AnimationState state) {
    animationState = state;
}

AnimationState HashTable::getAnimationState() {
    return animationState;
}

void HashTable::clearRedo() {
    redoStack.clear();
}
void HashTable::clearHistory() {
    actionHistory.clear();
}   
bool HashTable::canUndo() {
    return !actionHistory.empty();
}

bool HashTable::canRedo() {
    return !redoStack.empty();
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

    if (animationState == PAUSED) return;

    if (animationState == FINALIZE) {
        resetHighlights();
        std::queue<int> empty;
        std::swap(highlightQueue, empty);
        if (!addQueue.empty()) {
            int index = addQueue.front().first;
            int value = addQueue.front().second;
            addQueue.pop();
            highlightQueue.push(index);
            table[index].setValue(value);
        }
        if (!removeQueue.empty()) {
            int index = removeQueue.front();
            removeQueue.pop();
            highlightQueue.push(index);
            table[index].setValue(EMPTY);
        }
        if (!findQueue.empty()) {
            int index = findQueue.front();
            findQueue.pop();
            table[index].setPersistentHighlight();
        }
        if (sequentialRender) sequentialRender = false;
        animationState = IDLESTATE;
        return;
    }
    static float highlightTimer = 0.0f; 
    highlightTimer -= deltaTime;

    if (!highlightQueue.empty() && highlightTimer <= 0.0f) {
        highlightedIndex = highlightQueue.front();
        highlightQueue.pop();
        table[highlightedIndex].setHighlight(highlightDuration);
        displayHash++;
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
            animationState = IDLESTATE;
            highlightedIndex = -1;
        }
        if (!removeQueue.empty()) {
            int index = removeQueue.front();
            removeQueue.pop();
            table[index].setValue(EMPTY);
            animationState = IDLESTATE;
            highlightedIndex = -1;
        }
        if (!findQueue.empty()) {
            int index = findQueue.front();
            findQueue.pop();
            table[index].setPersistentHighlight();
            animationState = IDLESTATE;
            highlightedIndex = -1;
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
        if (animationState == PAUSED) return;
        renderTimer -= deltaTime;
        if (renderTimer <= 0.0f) { 
            if (toRender < size) {
                toRender++; 
                renderTimer = sequentialDuration; 
            } else {
                sequentialRender = false;
                animationState = IDLESTATE;
                toRender = 0;
            }
        }
    } else  {  
        for (int i = 0; i < size; i++) {
            table[i].render();
        }
    }
    std::ostringstream hashFunc;
    if (!isEmpty() && !highlightTask) {
        //displayValue = 0;
        displayHash = -1;
        highlightedIndex = -1;
        hashFunc << "Current hash function: (key % " << hashPrime << " + " << hashPrime << ") % " << size;    
        if (areFontsLoaded())DrawTextEx(FuturaBold, hashFunc.str().c_str(), {startX, 35}, 20, 2, BLACK);
        else DrawText(hashFunc.str().c_str(), startX, 35, 20, BLACK);
    }

    if (highlightedIndex != -1 && highlightTask) {
        hashFunc << "Probing: ((" << displayValue << " % " << hashPrime << " + " << hashPrime << ") % " << size << "+" << displayHash <<") % " << size << " = " << highlightedIndex;
        if (areFontsLoaded())DrawTextEx(FuturaBold, hashFunc.str().c_str(), {startX, 35}, 20, 2, BLACK);
        else DrawText(hashFunc.str().c_str(), startX, 35, 20, BLACK);    
    }
}