#include "HashTableScreen.h"

HashTableScreen::HashTableScreen(): hashTable(10), input({startX, 820}, {1000, 50}, LIGHTGRAY, BLACK, 30), goBack(false), inputTask(false), addMode(false), removeMode(false), searchMode(false), randomMode(false), resizeMode(false) {    
    bold = FuturaBold;
    normal = FuturaMedium;
    FontsLoaded = areFontsLoaded();

    back.setPosition({ 30, 25 });
    back.setText("<<<", 35);
    back.setSize({50, 50 });
    back.SetColor(BLANK, BEIGE, BLANK);

    clear.setPosition({ 60, 330 });
    clear.setText("Clear", 25);
    clear.setSize({175, 50 });
    clear.SetColor(BEIGE, BROWN, DARKBROWN);

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
    randomConfirm.SetColor(BLANK, BLANK, BLANK);

    resize.setPosition({ 60, 680 });
    resize.setText("Resize", 25);
    resize.setSize({ 175, 50 });
    resize.SetColor(BEIGE, BROWN, DARKBROWN);

    speedToggle.setPosition({ 60, 750});
    speedToggle.setText("Speed", 25);
    speedToggle.setSize({ 100, 50 });
    speedToggle.SetColor(BEIGE, BROWN, DARKBROWN);

    confirm.setPosition({ startX + 1000, 820 });
    confirm.setText("Confirm", 25);
    confirm.setSize({ 150, 50 });
    confirm.SetColor(LIGHTGRAY, GRAY, DARKBROWN);
}
HashTableScreen::~HashTableScreen() {
    hashTable.~HashTable();
}

bool HashTableScreen::isValidInput(std::string& s) {
    size_t spacePos = s.find(' ');

    if (spacePos != std::string::npos) {
        s = s.substr(0, spacePos);
    }

    if (s.empty()) return false;

    if (s.size() > 4) return false; 
    if (s[0] == '-' && s.size() == 1) return false;
    int start = (s[0] == '-') ? 1 : 0;

    for (int i = start; i < s.size(); i++) {
        if (!isdigit(s[i])) return false; 
    }

    return true; 
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
    back.update();
    add.update();
    speedToggle.update();
    randomConfirm.update();
    remove.update();
    search.update();
    random.update();
    resize.update();
    clear.update();

    input.update();
    confirm.update();

    if (clear.isClicked()) {
        hashTable.resize(0);
        disableModes();
    }

    if (back.isClicked()) {
        goBack = true;
        disableModes();
    }

    if (add.isClicked()) {
        disableModes();
        addMode = true;
        inputTask = true;
        input.setText("");
        input.setBoxTitle("Enter a value from -999 to 999");
    }

    if (addMode) {
        std::string toInput = input.getText();
        if ( (confirm.isClicked() || IsKeyPressed(KEY_ENTER)) && isValidInput(toInput) ) {
            int value = std::stoi(toInput);
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
        input.setBoxTitle("Enter a value from -999 to 999");
    }

    if (removeMode) {
        std::string toInput = input.getText();
        if ((confirm.isClicked() || IsKeyPressed(KEY_ENTER)) && isValidInput(toInput)) {
            int value = std::stoi(toInput);
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
        input.setBoxTitle("Enter a value from -999 to 999");
    }

    if (searchMode) {
        std::string toInput = input.getText();;
        if ((confirm.isClicked() || IsKeyPressed(KEY_ENTER)) && isValidInput(toInput)) {
            int value = std::stoi(toInput);
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
        input.setBoxTitle("Enter a value from 0 to 70");
    }

    if (resizeMode) {
        std::string toInput = input.getText();
        if ((confirm.isClicked() || IsKeyPressed(KEY_ENTER)) && isValidInput(toInput)) {
            int value = std::stoi(toInput);
            if (value < 0) return;
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
        if ((randomConfirm.isClicked() || IsKeyPressed(KEY_ENTER))) {
            hashTable.randomTable();
            randomMode = false;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !random.isHover() && !randomConfirm.isHover()) {
            randomMode = false;
        }
    }

    if (speedToggle.isClicked()) {
        hashTable.currentCoefficient++;
        hashTable.setHighlightCoefficient(hashTable.coefficients[hashTable.currentCoefficient%4]);
        hashTable.setRenderCoefficient(hashTable.coefficients[hashTable.currentCoefficient%4]);
    }
}

void HashTableScreen::render() {
    DrawRectangle(0, 0, 300, 900, { 211, 176, 131, 100 });
    DrawRectangle(15, 15, 270, 870, { 211, 176, 131, 120 });

    if (!FontsLoaded) {
        DrawText("HASH TABLE", 50, 150, 30, BLACK);
        //DrawText("----------", 75, 190, 30, BLACK);
        DrawLineEx({50 + (float)(MeasureText("HASH TABLE", 30) - 145)/2, 200}, {50 + (float)(MeasureText("HASH TABLE", 30) - 145)/2 + 145, 200}, 3, BLACK);
        DrawText("Linear Probing", (300 - (float)MeasureText("Linear Probing", 30))/2, 230, 30, BLACK);
    } else {
        float firstX = (300-MeasureTextEx(bold, "HASH TABLE", 50, 2).x)/2;
        DrawTextEx(bold, "HASH TABLE", {firstX,150}, 50, 2, BLACK);
        DrawLineEx({firstX + (MeasureTextEx(bold, "HASH TABLE", 50, 2).x - 145)/2, 212}, {50 + (MeasureTextEx(bold, "HASH TABLE", 50, 2).x - 145)/2 + 145,212}, 2, BLACK);
        DrawTextEx(normal, "Linear Probing", {(300 - MeasureTextEx(normal, "Linear Probing", 40, 2).x)/2, 230}, 40, 2, BLACK);
    }
    
    speedToggle.drawRectangle();
    speedToggle.drawOutline(0, 0, 2, BLACK);
    std::ostringstream currentSpeed;
    currentSpeed << std::fixed << std::setprecision(1) << hashTable.coefficients[hashTable.currentCoefficient%4] << "x";

    back.drawRectangle();
    //back.drawOutline(0, 0, 1, BLACK);

    clear.drawRectangle();
    clear.drawOutline(0, 0, 2, BLACK);

    add.drawRectangle();
    add.drawOutline(0, 0, 2, BLACK);
    

    remove.drawRectangle();
    remove.drawOutline(0, 0, 2, BLACK);
    

    search.drawRectangle();
    search.drawOutline(0, 0, 2, BLACK);
    

    random.drawRectangle();
    random.drawOutline(0, 0, 2, BLACK);
    

    resize.drawRectangle();
    resize.drawOutline(0, 0, 2, BLACK);
    
    if (!FontsLoaded) {
        speedToggle.drawText(BLACK);
        DrawText(currentSpeed.str().c_str(), 170, 750 + 12.5, 25, BLACK);
        clear.drawText(BLACK);
        back.drawText(BLACK);
        add.drawText(BLACK);
        remove.drawText(BLACK);
        search.drawText(BLACK);
        random.drawText(BLACK);
        resize.drawText(BLACK);
    }
    else {
        DrawTextEx(normal, "<<<", { 30 + (50 - MeasureTextEx(bold, "<<<", 25, 0.5).x)/2 , 25 + (50 - MeasureTextEx(bold, "<<<", 25, 0.5).y)/2}, 25, 0.5, BLACK);
        DrawTextEx(normal, "Speed", { 60 + (100 - MeasureTextEx(normal, "Speed", 30, 1).x)/2 , 750 + (50 - MeasureTextEx(normal, "Speed", 30, 1).y)/2}, 30, 1, BLACK);
        DrawTextEx(bold, currentSpeed.str().c_str(), { 180, 750 + 15}, 30, 1, BLACK);
        DrawTextEx(normal, "Clear", { 60 + (175 - MeasureTextEx(normal, "Clear", 30, 1).x)/2 , 330 + (50 - MeasureTextEx(normal, "Clear", 30, 1).y)/2}, 30, 1, BLACK);
        DrawTextEx(normal, "Add", { 60 + (175 - MeasureTextEx(normal, "Add", 30, 1).x)/2 , 400 + (50 - MeasureTextEx(normal, "Add", 30, 1).y)/2}, 30, 1, BLACK);
        DrawTextEx(normal, "Remove", { 60 + (175 - MeasureTextEx(normal, "Remove", 30, 1).x)/2 , 470 + (50 - MeasureTextEx(normal, "Remove", 30, 1).y)/2}, 30, 1, BLACK);
        DrawTextEx(normal, "Search", { 60 + (175 - MeasureTextEx(normal, "Search", 30, 1).x)/2 , 540 + (50 - MeasureTextEx(normal, "Search", 30, 1).y)/2}, 30, 1, BLACK);
        DrawTextEx(normal, "Randomize", { 60 + (175 - MeasureTextEx(normal, "Randomize", 30, 1).x)/2 , 610 + (50 - MeasureTextEx(normal, "Randomize", 30, 1).y)/2}, 30, 1, BLACK);
        DrawTextEx(normal, "Resize", { 60 + (175 - MeasureTextEx(normal, "Resize", 30, 1).x)/2 , 680 + (50 - MeasureTextEx(normal, "Resize", 30, 1).y)/2}, 30, 1, BLACK);
    }

    hashTable.render();

    if (inputTask) {
        input.render();
        confirm.drawRectangle();
        confirm.drawText(BLACK);
        confirm.drawOutline(0, 0, 2, BLACK);
    }
    if (randomMode) {
        randomConfirm.drawRectangle();
        if (!FontsLoaded) randomConfirm.drawText(BLACK);
        else DrawTextEx(bold, "GO", { 245, 610+15}, 30, 1, BLACK);
    }
}