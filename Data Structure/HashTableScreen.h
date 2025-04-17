#pragma once
#include "Button.h"
#include "Setting.h"
#include "TextBox.h"
#include "HashTable.h"
#include "Font.h"
#include "Icons.h"
#include "HashTableCode.h"

class HashTableScreen {
public:
    HashTableScreen();
    ~HashTableScreen();
    
    	bool goBack();
    void update();    
    void render();
    void disableModes();
private:
    bool FontsLoaded;

    HashTable hashTable;
    
    Font bold;
    Font normal;

    Button Home;
    Button add;
    Button remove;
    Button search;
    Button random;
    Button randomConfirm;
    Button resize;
    Button clear;

    Button undo;
    Button redo;
    Button pause;
    Button finalize;
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

