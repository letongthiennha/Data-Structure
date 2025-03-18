//#include "Button.h"
//
//	//Constructor
//	Button::Button(float x, float y, float width, float height, std::string text) {
//		this->pos.x = x;	this->hitBox.x = x;
//		this->pos.y = y;	this->hitBox.y = y;
//		this->height = height;	this->hitBox.height = height;
//		this->width = width;	this->hitBox.width = width;
//		this->text = text;
//		ComputeTextPos();
//	}
//
//	//Text
//	void Button:: ComputeTextPos() {
//
//		// Center text
//		int textWidth = MeasureText(text.c_str(), textSize);
//		this->textPos.x = pos.x + (width - textWidth) / 2;
//		this->textPos.y = pos.y + (height - textSize) / 2;
//	}
//	void Button::SetTextSize(int textSize)  {
//    this->textSize = textSize;
//    ComputeTextPos();
//	}
//	void Button::SetTextPos(Vector2 TextPos) {
//		this->textPos = TextPos;
//	}
//
//	// Mouse 
//	bool Button::isHover() const {
//		return(CheckCollisionPointRec(GetMousePosition(), this->hitBox) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
//	}
//
//	bool Button::isClicked() const {
//		return(CheckCollisionPointRec(GetMousePosition(), this->hitBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
//	}
//
//	//Set color
//	void Button::SetActiveColor(Color color) { activeColor = color; }
//	void Button::SetHoverColor(Color color) { hoverColor = color; }
//	void Button::SetIdleColor(Color color) { idleColor = color; }
//
//
//	//Update
//	void Button::update() {
//		if (this->isClicked()) {
//			renderColor = activeColor;
//			activeTimer = clickDuration;
//		}
//		if (activeTimer > 0) {
//			renderColor = activeColor;
//			activeTimer -= GetFrameTime();
//		}
//		else
//		if (this->isHover()) renderColor = hoverColor;
//
//		else renderColor = idleColor;
//	}
//	//Render
//	void Button::render() {
//		
//		DrawRectangle(pos.x, pos.y, width, height, renderColor);
//		// Draw text
//		DrawText(text.c_str(), static_cast<int>(textPos.x), static_cast<int>(textPos.y), textSize, BLUE);
//	}
