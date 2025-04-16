#include "HashTableScreen.h"
#include "Setting.h"
HashTableScreen::HashTableScreen() {
	Home = Button(homeButtonPosition, homeButtonSize, "Home");
	Home.SetIdleColor(controllerIdleColor);
	Home.SetHoverColor(controllerHoveringColor);
	Home.SetActiveColor(controllerActiveColor);
	Home.setTexture("assets/Icon/home.png");
}
void HashTableScreen::render() {
	Home.drawTexture();
	DrawText("Hash Table Screen", 800, 400, 20, BLACK);
}
void HashTableScreen::update() {
}
bool HashTableScreen::goBack() {
	if (Home.isClicked()) {
		return true;
	}
	return false;
}