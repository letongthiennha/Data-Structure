#pragma once
#include "Button.h"
#include "Setting.h"
#include "TextBox.h"
#include "HashTable.h"

class HashTableScreen {
public:
    HashTableScreen();
    ~HashTableScreen();
    
    void update();    
    void render();
    void disableModes();
private:
    HashTable hashTable;

    Button add;
    Button remove;
    Button search;
    Button random;
    Button randomConfirm;
    Button resize;
    Button clear;

    TextBox input;
    bool inputTask;
    Button confirm;

    bool addMode;
    bool removeMode;
    bool searchMode;
    bool randomMode;
    bool resizeMode;
};