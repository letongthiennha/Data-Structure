#include "Application.h"
#include "AVLScreen.h"
Application::Application() {

	mainMenu = MenuScreen();
	SLL = SLLScreen();
    tree = AVLTree();
	HashTable = HashTableScreen();
	ShortestPath = ShortestPathScreen();
}

void Application::run() {

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (mainMenu.screenChoose) {
        case (Screen::MainMenu):
            mainMenu.update();
            mainMenu.render();
            break;
        case (Screen::SLL):
            SLL.update();
            SLL.render();
            if (SLL.goBack()) {
                mainMenu.screenChoose = Screen::MainMenu;
            }
            break;
        case Screen::AVL:

            std::string inputText = "";

            if (IsKeyPressed(KEY_ENTER) && !inputText.empty()) {
                tree.insert(std::stoi(inputText));
                inputText = "";
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !inputText.empty()) {
                inputText.pop_back();
            }
            int key = GetCharPressed();
            if (key >= '0' && key <= '9') {
                inputText += static_cast<char>(key);
            }
            tree.processInsertion();
            tree.updateNodePosition(tree.root);
            tree.drawTree();
            DrawText(("Enter number: " + inputText).c_str(), 10, 10, 20, DARKGRAY);
            break;
        case Screen::HashTable:
            HashTable.update();
            HashTable.render();
            
            break;
        case Screen::ShortestPath:
            ShortestPath.update();
            ShortestPath.render();
            if (ShortestPath.goBack()) {
                mainMenu.screenChoose = Screen::MainMenu;
            }
            break;
        default:
            break;
        }
        EndDrawing();
    }
}
