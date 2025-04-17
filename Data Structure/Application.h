#pragma once

#include "Menu Screen.h"
#include "SLLScreen.h"
#include "AVLScreen.h"
#include "HashTableScreen.h"
#include "ShortestPathScreen.h"


class Application {
public:
    Application();
    void run();
private:
    MenuScreen mainMenu;
    SLLScreen SLL;
    AVLTree tree;
    HashTableScreen HashTable;
    ShortestPathScreen ShortestPath;
};

