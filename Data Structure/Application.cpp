#include "Application.h"
#include "AVLScreen.h"
Application::Application() {

	mainMenu = MenuScreen();
	SLL = SLLScreen();
	AVL = AVLScreen();
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
            AVL.update();
            AVL.render();
            if (AVL.goBack()) {
                mainMenu.screenChoose = Screen::MainMenu;
            }
            break;
        case Screen::HashTable:
            HashTable.update();
            HashTable.render();
            if (AVL.goBack()) {
                mainMenu.screenChoose = Screen::MainMenu;
            }
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
