#pragma once
#include "raylib.h"
#include "AVL.h"
#include "Button.h"
#include "Setting.h"
#include <string>
#include "TextBox.h"
#include "Slider.h"

class AVLScreen {
private:
    Button HomeButton;  // Đổi tên để tránh trùng lặp
    Button Create;
    Button Random;
    Button Insert;
    Button Remove;
    Button Find;
    Button Update;
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
    bool goBack();  // Hàm goBack tương thích với SLLScreen
    void render();
    void updateList();
    void update();
};