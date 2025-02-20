#include "Button.h"

	//Constructor
	Button::Button(float x, float y, float width, float height, std::string text) {
		this->rect.x = x;
		this->rect.y = y;
		this->rect.height = height;
		this->rect.width = width;
		this->text = text;
		ComputeTextPos();
	}
	//Compute text box
	void Button:: ComputeTextPos() {

		int maxWidth = rect.width - 10;  // Leave padding

		// Adjust font size to fit within the button width
		while (MeasureText(text.c_str(), textSize) > maxWidth && textSize > 10) {
			textSize--;  // Reduce size if text is too big
		}

		// Center text
		int textWidth = MeasureText(text.c_str(), textSize);
		this->textPos.x = rect.x + (rect.width - textWidth) / 2;
		this->textPos.y = rect.y + (rect.height - textSize) / 2;
	}


	// Mouse 
	bool Button::isHover() const {
		if (CheckCollisionPointRec(GetMousePosition(), this->rect) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return true;
		}
		return false;
	}
	bool Button::isClicked() const {
		if (CheckCollisionPointRec(GetMousePosition(), this->rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return true;
		}
		return false;
	}
	//Set color
	void Button::SetActiveColor(Color color) { activeColor = color; };
	void Button::SetHoverColor(Color color) { hoverColor = color; };
	void Button::SetIdleColor(Color color) { idleColor = color; ; }

	//Render
	void Button::render() {
		Color renderColor;
		if (this->isHover()) renderColor = hoverColor;
		else
			if (this->isClicked()) renderColor = activeColor;
			else renderColor = idleColor;

		DrawRectangleRec(this->rect, renderColor);

		// Draw text
		DrawText(text.c_str(), static_cast<int>(textPos.x), static_cast<int>(textPos.y), textSize, BLUE);
	}
