#pragma once
#include "Button.h"
#include "Setting.h"
#include "TextBox.h"
#include "HashTable.h"
#include "HashTableFonts.h"
#include "HashTableCode.h"

class HashTableScreen {
public:
    HashTableScreen();
    ~HashTableScreen();
    
    void update();    
    void render();
    void disableModes();
private:
    HashTable hashTable;
    
    Font bold;
    Font normal;

    Button add;
    Button remove;
    Button search;
    Button random;
    Button randomConfirm;
    Button resize;
    Button clear;
    Button speedToggle;

    TextBox input;
    bool inputTask;
    bool isValidInput(std::string& s);
    Button confirm;

    bool addMode;
    bool removeMode;
    bool searchMode;
    bool randomMode;
    bool resizeMode;
};

