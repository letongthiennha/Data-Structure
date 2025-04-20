#include "AVLScreen.h"
#include "Motion.h"
#include "Button.h"
#include "raylib.h"
#include "Setting.h"
#include "AVL.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>

AVLScreen::AVLScreen() {
    speedChooser.setPosition({ 1400, 50 });
    speedChooser.setSize({ 20, 200 });

    inputBox.setPosition({ 50, 830 });
    inputBox.setBoxTitle("Input");
    inputBox.setMaxLength(10);
    inputBox.setBoxSize({ 200, 70 });

    HomeButton = Button(homeButtonPosition, homeButtonSize, "Home");
    HomeButton.SetIdleColor(controllerIdleColor);
    HomeButton.SetHoverColor(controllerHoveringColor);
    HomeButton.SetActiveColor(controllerActiveColor);
    HomeButton.setTexture("assets/Icon/home.png");

    Create = Button({ 100, 500 }, stateControlButtonSize, "Create");
    Create.SetIdleColor(controllerIdleColor);
    Create.SetHoverColor(controllerHoveringColor);
    Create.SetActiveColor(controllerActiveColor);

    Random = Button({ 100, 550 }, stateControlButtonSize, "Random");
    Random.SetIdleColor(controllerIdleColor);
    Random.SetHoverColor(controllerHoveringColor);
    Random.SetActiveColor(controllerActiveColor);

    Insert = Button({ 100, 600 }, stateControlButtonSize, "Insert");
    Insert.SetIdleColor(controllerIdleColor);
    Insert.SetHoverColor(controllerHoveringColor);
    Insert.SetActiveColor(controllerActiveColor);

    Remove = Button({ 100, 650 }, stateControlButtonSize, "Remove");
    Remove.SetIdleColor(controllerIdleColor);
    Remove.SetHoverColor(controllerHoveringColor);
    Remove.SetActiveColor(controllerActiveColor);

    Find = Button({ 100, 700 }, stateControlButtonSize, "Find");
    Find.SetIdleColor(controllerIdleColor);
    Find.SetHoverColor(controllerHoveringColor);
    Find.SetActiveColor(controllerActiveColor);

    Update = Button({ 100, 750 }, stateControlButtonSize, "Update");
    Update.SetIdleColor(controllerIdleColor);
    Update.SetHoverColor({ 85, 156, 236, 255 });
    Update.SetActiveColor(controllerActiveColor);

    Accept = Button({ 300, 850 }, stateControlButtonSize, "");
    Accept.setTexture("assets/Icon/accept.png");
    Accept.SetIdleColor(controllerIdleColor);
    Accept.SetHoverColor({ 85, 156, 236, 255 });
    Accept.SetActiveColor(controllerActiveColor);

    Pause = Button(stateControlPosition, homeButtonSize, "Pause");
    Pause.setTexture("assets/Icon/pause.png");
    Pause.SetIdleColor(controllerIdleColor);
    Pause.SetHoverColor({ 85, 156, 236, 255 });
    Pause.SetActiveColor(controllerActiveColor);

    Skip = Button(Vector2Add(stateControlPosition, Vector2{ 100, 0 }), homeButtonSize, "Skip");
    Skip.setTexture("assets/Icon/skip.png");
    Skip.SetIdleColor(controllerIdleColor);
    Skip.SetHoverColor({ 85, 156, 236, 255 });
    Skip.SetActiveColor(controllerActiveColor);
}

void AVLScreen::updateList() {
    myTree.update();

    float speed = speedChooser.getProgress();
    if (speed < 0.01f) speed = 0.01f;  // Đảm bảo tốc độ tối thiểu là 0.01
    myTree.setSpeed(speed);

    if (inputting) {
        inputBox.update();
        Accept.update();
    }
    if (Accept.isClicked()) {
        if (!inputBox.isEmpty()) {
            if (choose == AVLOperationType::CREATE) {
                std::string input = inputBox.getText();
                std::vector<int> vals;
                std::stringstream ss(input);
                int val;
                while (ss >> val) {
                    vals.push_back(val);
                    if (ss.peek() == ' ') ss.ignore();
                }
                myTree.create(vals);
            }
            if (choose == AVLOperationType::UPDATE) {
                std::string input = inputBox.getText();
                int oldValue = std::stoi(input.substr(0, input.find(" ")));
                int newValue = std::stoi(input.substr(input.find(" ") + 1));
                myTree.storeOperation(AVLOperationType::UPDATE, oldValue, newValue);
            }
            else {
                int input = std::stoi(inputBox.getText());
                switch (choose) {
                case AVLOperationType::RANDOM: myTree.storeOperation(AVLOperationType::RANDOM, input); break;
                case AVLOperationType::INSERT: myTree.storeOperation(AVLOperationType::INSERT, input); break;
                case AVLOperationType::REMOVE: myTree.storeOperation(AVLOperationType::REMOVE, input); break;
                case AVLOperationType::FIND: myTree.storeOperation(AVLOperationType::FIND, input); break;
                }
            }
        }
        inputBox.clearContent();
        inputting = false;
        choose = AVLOperationType::NONE;
    }
}

void AVLScreen::update() {
    Random.update();
    Create.update();
    Insert.update();
    Remove.update();
    Find.update();
    Update.update();
    HomeButton.update();
    Pause.update();
    Skip.update();
    speedChooser.update();

    if (Random.isClicked()) {
        inputting = true;
        choose = AVLOperationType::RANDOM;
        inputBox.setBoxTitle("Input Amount");
    }
    if (Create.isClicked()) {
        inputting = true;
        choose = AVLOperationType::CREATE;
        inputBox.setBoxTitle("Input Value");
    }
    if (Insert.isClicked()) {
        inputting = true;
        choose = AVLOperationType::INSERT;
        inputBox.setBoxTitle("Input Value");
    }
    if (Remove.isClicked()) {
        inputting = true;
        choose = AVLOperationType::REMOVE;
        inputBox.setBoxTitle("Input Value");
    }
    if (Find.isClicked()) {
        inputting = true;
        choose = AVLOperationType::FIND;
        inputBox.setBoxTitle("Input Value");
    }
    if (Update.isClicked()) {
        inputting = true;
        choose = AVLOperationType::UPDATE;
        inputBox.setBoxTitle("Input (OldValue NewValue)");
    }
    if (Pause.isClicked()) {
        myTree.setStop(!myTree.isStop());
        if (myTree.isStop()) {
            Pause.setTexture("assets/Icon/play.png");
        }
        else {
            Pause.setTexture("assets/Icon/pause.png");
        }
    }
    if (Skip.isClicked()) myTree.setSkip();
    if (IsFileDropped()) {
        FilePathList droppedFiles = LoadDroppedFiles();
        std::string path = droppedFiles.paths[0];
        if (droppedFiles.count > 0) {
            myTree.LoadFromFile(droppedFiles.paths[0]);
        }
        UnloadDroppedFiles(droppedFiles);
    }
    updateList();
    inputBox.update();
}

void AVLScreen::render() {
    Create.renderRectangle();
    Create.drawTexture();
    Create.drawOutline(10, 10, 2, BLACK);
    Create.drawText({ 0, 0, 0, 255 });

    Random.renderRectangle();
    Random.drawTexture();
    Random.drawOutline(10, 10, 2, BLACK);
    Random.drawText({ 0, 0, 0, 255 });

    Insert.renderRectangle();
    Insert.drawTexture();
    Insert.drawOutline(10, 10, 2, BLACK);
    Insert.drawText({ 0, 0, 0, 255 });

    Remove.renderRectangle();
    Remove.drawTexture();
    Remove.drawOutline(10, 10, 2, BLACK);
    Remove.drawText({ 0, 0, 0, 255 });

    Find.renderRectangle();
    Find.drawTexture();
    Find.drawOutline(10, 10, 2, BLACK);
    Find.drawText({ 0, 0, 0, 255 });

    Update.renderRectangle();
    Update.drawTexture();
    Update.drawOutline(10, 10, 2, BLACK);
    Update.drawText({ 0, 0, 0, 255 });

    HomeButton.drawTexture();

    Skip.drawTexture();

    Pause.drawTexture();

    if (inputting) {
        inputBox.render();
        Accept.drawTexture();
    }

    speedChooser.render();

    myTree.render();
}

bool AVLScreen::goBack() {
    return HomeButton.isClicked();
}