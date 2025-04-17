#include "HashTableScreen.h"
#include "Setting.h"
#include "Icons.h"
HashTableScreen::HashTableScreen(): hashTable(10), input({startX, 820}, {1000, 50}, LIGHTGRAY, BLACK, 30), inputTask(false), addMode(false), removeMode(false), searchMode(false), randomMode(false), resizeMode(false) {    
    bold = FuturaBold;
    normal = FuturaMedium;
    FontsLoaded = areFontsLoaded();


    clear.setPosition({ 60, 310 });
    clear.setText("Clear", 25);
    clear.setSize({175, 50 });
    clear.SetColor(BEIGE, BROWN, DARKBROWN);

    add.setPosition({ 60, 380 });
    add.setText("Add", 25);
    add.setSize({175, 50 });
    add.SetColor(BEIGE, BROWN, DARKBROWN);

    remove.setPosition({ 60, 450 });
    remove.setText("Remove", 25);
    remove.setSize({175, 50 });
    remove.SetColor(BEIGE, BROWN, DARKBROWN);
    
    search.setPosition({ 60, 520 });
    search.setText("Search", 25);
    search.setSize({175, 50 });
    search.SetColor(BEIGE, BROWN, DARKBROWN);

    random.setPosition({ 60, 590 });
    random.setText("Randomize", 25);
    random.setSize({ 175, 50 });
    random.SetColor(BEIGE, BROWN, DARKBROWN);

    randomConfirm.setPosition({ 235, 590 });
    randomConfirm.setText("GO", 22);
    randomConfirm.setSize({ 52, 50 });
    randomConfirm.SetColor(BLANK, BLANK, BLANK);

    resize.setPosition({ 60, 660 });
    resize.setText("Resize", 25);
    resize.setSize({ 175, 50 });
    resize.SetColor(BEIGE, BROWN, DARKBROWN);

    speedToggle.setPosition({ 60, 730});
    speedToggle.setText("Speed", 25);
    speedToggle.setSize({ 100, 50 });
    speedToggle.SetColor(BEIGE, BROWN, DARKBROWN);

    confirm.setPosition({ startX + 1000, 820 });
    confirm.setText("Confirm", 25);
    confirm.setSize({ 150, 50 });
    confirm.SetColor(LIGHTGRAY, GRAY, DARKBROWN);

    undo.setPosition({ 35, 820 });
    undo.setText("Undo", 25);
    undo.setSize({ 50, 50 });
    undo.setTexture("assets/Icon/prev.png");
    undo.SetColor(BEIGE, BROWN, DARKBROWN);

    redo.setPosition({ 90, 820 });
    redo.setText("Redo", 25);
    redo.setSize({ 50, 50 });
    redo.setTexture("assets/Icon/next.png");

    redo.SetColor(BEIGE, BROWN, DARKBROWN);

    pause.setPosition({ 160, 820 });
    pause.setText("Pause", 25);
    pause.setTexture("assets/Icon/pause.png");
    pause.setSize({ 50, 50 });
    pause.SetColor(BEIGE, BROWN, DARKBROWN);

    finalize.setPosition({ 210, 820 });
    finalize.setText("Finalize", 25);
    finalize.setTexture("assets/Icon/skip.png");
    finalize.SetColor(BEIGE, BROWN, DARKBROWN);
    
  Home = Button(homeButtonPosition, homeButtonSize, "Home");
	Home.SetIdleColor(controllerIdleColor);
	Home.SetHoverColor(controllerHoveringColor);
	Home.SetActiveColor(controllerActiveColor);
	Home.setTexture("assets/Icon/home.png");
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
    hashTable.setAnimationState(FINALIZE);
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
    speedToggle.update();
    randomConfirm.update();
    remove.update();
    search.update();
    random.update();
    resize.update();
    clear.update();
    
    undo.update();
    redo.update();
    finalize.update();
    pause.update();

    input.update();
    confirm.update();

    if (clear.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
        hashTable.resize(0);
        hashTable.clearRedo();
        disableModes();
    }


    if (add.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
        //hashTable.clearRedo();
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
        hashTable.setAnimationState(FINALIZE);
        //hashTable.clearRedo();
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
            removeMode = false;
            hashTable.remove(value);
            inputTask = false;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !remove.isHover() && !confirm.isHover() && !input.isHover()) {
            inputTask = false;
            removeMode = false;
        }
    }

    if (search.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
        //hashTable.clearRedo();
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
            searchMode = false;
            inputTask = false;
            
        } 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !search.isHover() && !confirm.isHover() && !input.isHover()) {
            inputTask = false;
            searchMode = false;
        }
    }

    if (resize.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
        //hashTable.clearRedo();
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
            if (value < 0 || value > 70) return;
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
        hashTable.setAnimationState(FINALIZE);
        disableModes();
        randomMode = true;
    }

    if (randomMode) {
        //hashTable.clearRedo();
        if ((randomConfirm.isClicked() || IsKeyPressed(KEY_ENTER))) {
            randomMode = false;
            hashTable.randomTable();
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

    if (hashTable.canUndo() && undo.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
        hashTable.undo();
    }

    if (hashTable.canRedo() && redo.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
        hashTable.redo();
    }

    if (hashTable.getAnimationState() == PLAYING && finalize.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
    }

    if (pause.isClicked()) {

        if (hashTable.getAnimationState() == PAUSED) {
            hashTable.setAnimationState(PLAYING);
            pause.setTexture("assets/Icon/pause.png");

        }
        else if (hashTable.getAnimationState() == PLAYING) {
            hashTable.setAnimationState(PAUSED);
            pause.setTexture("assets/Icon/play.png");

        }
    }

    if (hashTable.getAnimationState() == FINALIZE || hashTable.getAnimationState() == PLAYING) {
        pause.setText("Pause", 25);
    } else {
        pause.setText("Play", 25);
    }

    if (!hashTable.canUndo()) undo.SetColor({ 128, 128, 128, 150 }, { 128, 128, 128, 150 }, { 128, 128, 128, 150 });
    else undo.SetColor(BEIGE, BROWN, DARKBROWN);
    if (!hashTable.canRedo()) redo.SetColor({ 128, 128, 128, 150 }, { 128, 128, 128, 150 }, { 128, 128, 128, 150 });
    else redo.SetColor(BEIGE, BROWN, DARKBROWN);
    
    if (hashTable.getAnimationState() == IDLESTATE) { 
        finalize.SetColor({ 128, 128, 128, 150 }, { 128, 128, 128, 150 }, { 128, 128, 128, 150 });
        pause.SetColor({ 128, 128, 128, 150 }, { 128, 128, 128, 150 }, { 128, 128, 128, 150 });
    } else {
        finalize.SetColor(BEIGE, BROWN, DARKBROWN);
        pause.SetColor(BEIGE, BROWN, DARKBROWN);
    }
}

void HashTableScreen::render() {
    DrawRectangle(0, 0, 300, 900, { 211, 176, 131, 100 });
    DrawRectangle(15, 15, 270, 870, { 211, 176, 131, 120 });

    if (!FontsLoaded) {
        DrawText("HASH TABLE", 50, 150, 30, BLACK);
        //DrawText("----------", 75, 190, 30, BLACK);
        DrawLineEx({ 50 + (float)(MeasureText("HASH TABLE", 30) - 145) / 2, 200 }, { 50 + (float)(MeasureText("HASH TABLE", 30) - 145) / 2 + 145, 200 }, 3, BLACK);
        DrawText("Linear Probing", (300.0 - (float)MeasureText("Linear Probing", 30)) / 2.0, 230, 30, BLACK);
    }
    else {
        float firstX = (300 - MeasureTextEx(bold, "HASH TABLE", 50, 2).x) / 2;
        DrawTextEx(bold, "HASH TABLE", { firstX,150 }, 50, 2, BLACK);
        DrawLineEx({ firstX + (MeasureTextEx(bold, "HASH TABLE", 50, 2).x - 145) / 2, 212 }, { 50 + (MeasureTextEx(bold, "HASH TABLE", 50, 2).x - 145) / 2 + 145,212 }, 2, BLACK);
        DrawTextEx(normal, "Linear Probing", { (300 - MeasureTextEx(normal, "Linear Probing", 40, 2).x) / 2, 230 }, 40, 2, BLACK);
    }

    speedToggle.renderRectangle();
    speedToggle.drawOutline(0, 0, 2, BLACK);
    std::ostringstream currentSpeed;
    currentSpeed << std::fixed << std::setprecision(1) << hashTable.coefficients[hashTable.currentCoefficient % 4] << "x";


    clear.renderRectangle();
    clear.drawOutline(0, 0, 2, BLACK);

    add.renderRectangle();
    add.drawOutline(0, 0, 2, BLACK);


    remove.renderRectangle();
    remove.drawOutline(0, 0, 2, BLACK);


    search.renderRectangle();
    search.drawOutline(0, 0, 2, BLACK);


    random.renderRectangle();
    random.drawOutline(0, 0, 2, BLACK);


    resize.renderRectangle();
    resize.drawOutline(0, 0, 2, BLACK);

    undo.drawTexture();

    redo.drawTexture();

    pause.drawTexture();

    finalize.drawTexture();

    if (!FontsLoaded) {
        speedToggle.drawText(BLACK);
        DrawText(currentSpeed.str().c_str(), 170, 750.0 + 12.5, 25, BLACK);
        clear.drawText(BLACK);
        //back.drawText(BLACK);
        add.drawText(BLACK);
        remove.drawText(BLACK);
        search.drawText(BLACK);
        random.drawText(BLACK);
        resize.drawText(BLACK);
        //undo.drawText(BLACK);
        //redo.drawText(BLACK);
        //pause.drawText(BLACK);
        //finalize.drawText(BLACK);
    }
    else {
        //DrawTextEx(normal, "<<<", { 30 + (50 - MeasureTextEx(bold, "<<<", 25, 0.5).x)/2 , 25 + (50 - MeasureTextEx(bold, "<<<", 25, 0.5).y)/2}, 25, 0.5, BLACK);
        DrawTextEx(normal, "Speed", { 60 + (100 - MeasureTextEx(normal, "Speed", 30, 1).x) / 2 , 730 + (50 - MeasureTextEx(normal, "Speed", 30, 1).y) / 2 }, 30, 1, BLACK);
        DrawTextEx(bold, currentSpeed.str().c_str(), { 180, 730 + 15 }, 30, 1, BLACK);
        DrawTextEx(normal, "Clear", { 60 + (175 - MeasureTextEx(normal, "Clear", 30, 1).x) / 2 , 310 + (50 - MeasureTextEx(normal, "Clear", 30, 1).y) / 2 }, 30, 1, BLACK);
        DrawTextEx(normal, "Add", { 60 + (175 - MeasureTextEx(normal, "Add", 30, 1).x) / 2 , 380 + (50 - MeasureTextEx(normal, "Add", 30, 1).y) / 2 }, 30, 1, BLACK);
        DrawTextEx(normal, "Remove", { 60 + (175 - MeasureTextEx(normal, "Remove", 30, 1).x) / 2 , 450 + (50 - MeasureTextEx(normal, "Remove", 30, 1).y) / 2 }, 30, 1, BLACK);
        DrawTextEx(normal, "Search", { 60 + (175 - MeasureTextEx(normal, "Search", 30, 1).x) / 2 , 520 + (50 - MeasureTextEx(normal, "Search", 30, 1).y) / 2 }, 30, 1, BLACK);
        DrawTextEx(normal, "Randomize", { 60 + (175 - MeasureTextEx(normal, "Randomize", 30, 1).x) / 2 , 590 + (50 - MeasureTextEx(normal, "Randomize", 30, 1).y) / 2 }, 30, 1, BLACK);
        DrawTextEx(normal, "Resize", { 60 + (175 - MeasureTextEx(normal, "Resize", 30, 1).x) / 2 , 660 + (50 - MeasureTextEx(normal, "Resize", 30, 1).y) / 2 }, 30, 1, BLACK);
    }

    hashTable.render();

    if (inputTask) {
        input.render();
        confirm.renderRectangle();
        confirm.drawText(BLACK);
        confirm.drawOutline(0, 0, 2, BLACK);
    }
    if (randomMode) {
        randomConfirm.renderRectangle();
        if (!FontsLoaded) randomConfirm.drawText(BLACK);
        else DrawTextEx(bold, "GO", { 245, 610 + 15 }, 30, 1, BLACK);
    }

    //DrawTextureEx(undoIcon, { undo.getPosition().x + 6, undo.getPosition().y + 8 }, 0, 0.075f, WHITE);
    //DrawTextureEx(redoIcon, { redo.getPosition().x + 6,  redo.getPosition().y + 8 }, 0, 0.075f, WHITE);
    //if (hashTable.getAnimationState() == PLAYING) DrawTextureEx(pauseIcon, { pause.getPosition().x + 9, pause.getPosition().y + 10 }, 0, 0.06f, WHITE);
    //else DrawTextureEx(play, { pause.getPosition().x + 15, pause.getPosition().y + 15 }, 0, 0.04f, WHITE);
    //DrawTextureEx(fastforward, { finalize.getPosition().x + 10, finalize.getPosition().y + 10 }, 0, 0.06f, WHITE);

    if (hashTable.getAnimationState() == PAUSED) {
        DrawRectangleLinesEx(Rectangle{ 0, 0, 1600, 900 }, 5, RED);
    }
    Home.drawTexture();
    DrawText("Hash Table Screen", 800, 400, 20, BLACK);
}
bool HashTableScreen::goBack() {
    if (Home.isClicked()) {
        hashTable.setAnimationState(FINALIZE);
        hashTable = HashTable(10);
        hashTable.clearRedo();
        hashTable.clearHistory();
        disableModes();
        return true;
    }
    return false;
};