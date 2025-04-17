#include "Menu Screen.h"

#include "raylib.h"
#include "Setting.h"
#include "Button.h"

MenuScreen::MenuScreen() {
	SLL = Button({ 400, 400 }, { 300, 169 }, "Singly Linked List");
	SLL.SetIdleColor(controllerIdleColor);
	SLL.SetHoverColor({ 85,156,236,255 });
	SLL.SetActiveColor(controllerActiveColor);
	SLL.setTexture("assets/Icon/SLL.png");

	AVL = Button({ 900, 400 }, { 300, 169 }, "AVL Tree");
	AVL.SetIdleColor(controllerIdleColor);
	AVL.SetHoverColor({ 85,156,236,255 });
	AVL.SetActiveColor(controllerActiveColor);
	AVL.setTexture("assets/Icon/AVL.png");
	
	HashTable = Button({ 400, 600 }, { 300, 169 }, "Hash Table");
	HashTable.SetIdleColor(controllerIdleColor);
	HashTable.SetHoverColor({ 85,156,236,255 });
	HashTable.SetActiveColor(controllerActiveColor);
	HashTable.setTexture("assets/Icon/HashTable.png");

	ShortestPath = Button({ 900, 600 }, { 300, 169 }, "Shortest Path");
	ShortestPath.SetIdleColor(controllerIdleColor);
	ShortestPath.SetHoverColor({ 85,156,236,255 });
	ShortestPath.SetActiveColor(controllerActiveColor);
	ShortestPath.setTexture("assets/Icon/Graph.png");

	exit = Button({ 50, 50 },homeButtonPosition, "Exit");
	exit.SetIdleColor(controllerIdleColor);
	exit.SetHoverColor({ 85,156,236,255 });
	exit.SetActiveColor(controllerActiveColor);
	exit.setTexture("assets/Icon/Exit.png");

	background = LoadTexture("assets/background.png");
}
void MenuScreen::render() {
	DrawTexture(background, 0, 0, WHITE);

	SLL.drawTexture();
	SLL.drawOutline(10, 10, 2, BLACK);

	AVL.drawTexture();
	AVL.drawOutline(10, 10, 2, BLACK);

	HashTable.drawTexture();
	HashTable.drawOutline(10, 10, 2, BLACK);

	ShortestPath.drawTexture();
	ShortestPath.drawOutline(10, 10, 2, BLACK);

	exit.drawTexture();
}
void MenuScreen::update() {
	if (SLL.isClicked()) {
		screenChoose = Screen::SLL;
	}
	if (AVL.isClicked()) {
		screenChoose = Screen::AVL;
	}
	if (HashTable.isClicked()) {
		screenChoose = Screen::HashTable;
	}
	if (ShortestPath.isClicked()) {
		screenChoose = Screen::ShortestPath;
	}
	if (exit.isClicked()) {
		CloseWindow();
	}
}