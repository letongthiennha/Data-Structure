#pragma once
#include "raylib.h"
#include "AVL.h"
#include "Button.h"
#include "Setting.h"
#include <string>
#include "TextBox.h"
#include "Slider.h"
#include "tinyfiledialogs.h"
    
class AVLScreen {
private:
    Button HomeButton;  
    Button Create;
    Button Random;
    Button Insert;
    Button Remove;
    Button Find;
    Button Update;
    Button LoadFile;
    Button Accept;
    Button Pause;
    Button Skip;

    Rectangle speed;

    AVLTree myTree;
    bool inputting;
    AVLOperationType choose = AVLOperationType::NONE;
    TextBox inputBox;
    int updateOldValue = 0;

    Slider speedChooser;

public:
    AVLScreen();
    bool goBack();  
    void render();
    void updateList();
    void update();
};