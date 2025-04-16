#pragma once
#include "Button.h"

enum class Screen {
    MainMenu,
    SLL,
    AVL,
    HashTable,
    ShortestPath
};

class MenuScreen {
public:  
	Screen screenChoose=Screen::MainMenu;
    MenuScreen();
    void render();
    void update();
private:
    Texture2D background;
    std::string title;

    //Button on screen
    Button exit;
    Button SLL;
    Button AVL;
    Button HashTable;
    Button ShortestPath;
};
