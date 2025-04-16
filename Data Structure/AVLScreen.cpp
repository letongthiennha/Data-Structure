#include "AVLScreen.h"
#include "Setting.h"
AVLScreen::AVLScreen() {
	Home = Button(homeButtonPosition, homeButtonSize, "Home");
	Home.SetIdleColor(controllerIdleColor);
	Home.SetHoverColor(controllerHoveringColor);
	Home.SetActiveColor(controllerActiveColor);
	Home.setTexture("assets/Icon/home.png");
}
void AVLScreen::renderList() {
	Home.drawTexture();
	DrawText("AVL Tree Screen", 800, 400, 20, BLACK);
}
void AVLScreen::update() {

}
bool AVLScreen::goBack() {
	if (Home.isClicked()) {
		return true;
	}
	return false;
}