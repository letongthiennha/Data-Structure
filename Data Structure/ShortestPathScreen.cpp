#include "ShortestPathScreen.h"
#include "Setting.h"
ShortestPathScreen::ShortestPathScreen() {
	Home = Button(homeButtonPosition, homeButtonSize, "Home");
	Home.SetIdleColor(controllerIdleColor);
	Home.SetHoverColor(controllerHoveringColor);
	Home.SetActiveColor(controllerActiveColor);
	Home.setTexture("assets/Icon/home.png");
}
void ShortestPathScreen::renderList() {
	Home.drawTexture();
	DrawText("Shortest Path Screen", 800, 400, 20, BLACK);
}
void ShortestPathScreen::update() {
	// Update the Shortest Path screen
}
bool ShortestPathScreen::goBack() {
	if (Home.isClicked()) {
		return true;
	}
	return false;
}
