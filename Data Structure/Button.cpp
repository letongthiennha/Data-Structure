#include "Button.h"

Button::Button(float x, float y, float width, float height, std::string text) {
	this->rect.x = x;
	this->rect.y = y;
	this->rect.height = height;
	this->rect.width = width;
	this->text = text;
}
void Button::render () {
	Color renderColor;
	if (this->isHover()) renderColor = hoverColor;
	else
	if (this->isClicked()) renderColor = activeColor;
	else renderColor = idleColor;

	DrawRectangleRec(this->rect, renderColor);

	// Auto-resize text to fit within the rectangle
	int fontSize = 20;  // Default size
	int maxWidth = rect.width - 10;  // Leave padding

	// Adjust font size to fit within the button width
	while (MeasureText(text.c_str(), fontSize) > maxWidth && fontSize > 10) {
		fontSize--;  // Reduce size if text is too big
	}

	// Center text inside the button
	int textWidth = MeasureText(text.c_str(), fontSize);
	int textX = rect.x + (rect.width - textWidth) / 2;
	int textY = rect.y + (rect.height - fontSize) / 2;

	// Draw text
	DrawText(text.c_str(), textX, textY, fontSize, WHITE);
}
bool Button::isHover() const{
	if (CheckCollisionPointRec(GetMousePosition(), this->rect) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return true;
	}
	return false;
}
bool Button::isClicked() const{
	if (CheckCollisionPointRec(GetMousePosition(), this->rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return true;
	}
	return false;
}
