#include "HashTableScreen.h"

HashTableScreen::HashTableScreen(): hashTable(10), input({startX, 820}, {1000, 50}, LIGHTGRAY, BLACK, 30), inputTask(false), addMode(false), removeMode(false), searchMode(false), randomMode(false), resizeMode(false) {

    add.setPosition({ 60, 400 });
    add.setText("Add", 25);
    add.setSize({175, 50 });
    add.SetColor(BEIGE, BROWN, DARKBROWN);

    remove.setPosition({ 60, 470 });
    remove.setText("Remove", 25);
    remove.setSize({175, 50 });
    remove.SetColor(BEIGE, BROWN, DARKBROWN);
    
    search.setPosition({ 60, 540 });
    search.setText("Search", 25);
    search.setSize({175, 50 });
    search.SetColor(BEIGE, BROWN, DARKBROWN);

    random.setPosition({ 60, 610 });
    random.setText("Randomize", 25);
    random.setSize({ 175, 50 });
    random.SetColor(BEIGE, BROWN, DARKBROWN);

    randomConfirm.setPosition({ 235, 610 });
    randomConfirm.setText("GO", 22);
    randomConfirm.setSize({ 52, 50 });
    randomConfirm.SetColor(LIGHTGRAY, GRAY, DARKBROWN);

    resize.setPosition({ 60, 680 });
    resize.setText("Resize", 25);
    resize.setSize({ 175, 50 });
    resize.SetColor(BEIGE, BROWN, DARKBROWN);

    confirm.setPosition({ startX + 1000, 820 });
    confirm.setText("Confirm", 25);
    confirm.setSize({ 150, 50 });
    confirm.SetColor(LIGHTGRAY, GRAY, DARKBROWN);
}
HashTableScreen::~HashTableScreen() {
    hashTable.~HashTable();
}

void HashTableScreen::disableModes() {
    addMode = false;
    removeMode = false;
    searchMode = false;
    resizeMode = false;
    randomMode = false;
    inputTask = false;
}

void HashTableScreen::update() {
    hashTable.update();
    add.update();
    remove.update();
    search.update();
    random.update();
    resize.update();
    clear.update();

    input.update();
    confirm.update();

    if (add.isClicked()) {
        disableModes();
        addMode = true;
        inputTask = true;
        input.setText("");
        input.setBoxTitle("Enter value");
        //input.setPosition({ 200, 100 });
    }

    if (addMode) {
        if (confirm.isClicked() && !input.getText().empty()) {
            int value = std::stoi(input.getText());
            hashTable.add(value);
            inputTask = false;
            addMode = false;
        } 
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !add.isHover() && !confirm.isHover() && !input.isHover()) {
            inputTask = false;
            addMode = false;
        }
    }

    if (remove.isClicked()) {
        disableModes();
        removeMode = true;
        inputTask = true;
        input.setText("");
        input.setBoxTitle("Enter value");
        //input.setPosition({ 200, 200 });
    }

    if (removeMode) {
        if (confirm.isClicked() && !input.getText().empty()) {
            int value = std::stoi(input.getText());
            hashTable.remove(value);
            inputTask = false;
            removeMode = false;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !remove.isHover() && !confirm.isHover() && !input.isHover()) {
            inputTask = false;
            removeMode = false;
        }
    }

    if (search.isClicked()) {
        disableModes();
        searchMode = true;
        inputTask = true;
        input.setText("");
        input.setBoxTitle("Enter value");
        //input.setPosition({ 200, 300 });
    }

    if (searchMode) {
        if (confirm.isClicked() && !input.getText().empty()) {
            int value = std::stoi(input.getText());
            hashTable.search(value);
            inputTask = false;
            searchMode = false;
        } 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !search.isHover() && !confirm.isHover() && !input.isHover()) {
            inputTask = false;
            searchMode = false;
        }
    }

    if (resize.isClicked()) {
        disableModes();
        resizeMode = true;
        inputTask = true;
        input.setText("");
        input.setBoxTitle("Enter value");
        //input.setPosition({ 200, 400 });
    }

    if (resizeMode) {
        if (confirm.isClicked() && !input.getText().empty()) {
            int value = std::stoi(input.getText());
            hashTable.resize(value);
            inputTask = false;
            resizeMode = false;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !resize.isHover() && !confirm.isHover() && !input.isHover()) {
            inputTask = false;
            resizeMode = false;
        }
    }

    if (random.isClicked()) {
        disableModes();
        randomMode = true;
    }

    if (randomMode) {
        if (randomConfirm.isClicked()) {
            hashTable.randomTable();
            randomMode = false;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !random.isHover() && !randomConfirm.isHover()) {
            randomMode = false;
        }
    }
}

void HashTableScreen::render() {
    DrawRectangle(0, 0, 300, 900, { 211, 176, 131, 100 });
    DrawRectangle(15, 15, 270, 870, { 211, 176, 131, 120 });

    DrawText("HASH TABLE", 50, 180, 30, BLACK);
    DrawText("----------", 75, 220, 30, BLACK);
    DrawText("Linear Probing", 40, 260, 30, BLACK);

    add.drawRectangle();
    add.drawOutline(0, 0, 2, BLACK);
    add.drawText(BLACK);
    //add.drawTexture();

    remove.drawRectangle();
    remove.drawOutline(0, 0, 2, BLACK);
    remove.drawText(BLACK);
    //remove.drawTexture();

    search.drawRectangle();
    search.drawOutline(0, 0, 2, BLACK);
    search.drawText(BLACK);
    //search.drawTexture();

    random.drawRectangle();
    random.drawOutline(0, 0, 2, BLACK);
    random.drawText(BLACK);
    //random.drawTexture();

    resize.drawRectangle();
    resize.drawOutline(0, 0, 2, BLACK);
    resize.drawText(BLACK);
    //resize.drawTexture();

    hashTable.render();

    if (inputTask) {
        input.render();
        confirm.drawRectangle();
        confirm.drawText(BLACK);
        confirm.drawOutline(0, 0, 2, BLACK);
    }
    if (randomMode) {
        randomConfirm.drawRectangle();
        randomConfirm.drawText(BLACK);
    }
}