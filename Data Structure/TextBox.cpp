#include "TextBox.h"
//=============================================BoxState=============================================
BoxState::BoxState() : GUIState(), m_outline_color(WHITE) {}

BoxState::BoxState(Color outline_color, Color backgroud_color, Vector2 position) {
	//Color
	m_outline_color = outline_color;
	m_main_color = backgroud_color;
	//Position
	m_pos = position;
}

void BoxState::setOutlineColor(Color color) {
	m_outline_color = color;
}
Color BoxState::getOutlineColor() {
	return m_outline_color;
}
//=============================================TextBox=============================================

TextBox::TextBox() {
	static_cast<BoxState*>(m_state.get());
}
TextBox::TextBox(float x, float y, std::string text) {
	m_state = std::make_unique<BoxState>(Color{ 255,255,255,255 }, Color{ 255,255,255,255 }, Vector2{ x,y });
	m_text.setContent(text);
	m_text.setPosition({ x, y });
}
//=================================================Text Function=======================================
void TextBox::setText(std::string text) {
	m_text.setContent(text);
}
void TextBox::setTextColor(Color color) {
	m_text.setMainColor(color);
}
void TextBox::setTextSize(int textSize) {
	m_text.setTextSize(textSize);
}
void TextBox::setFont(Font font) {
	m_text.setFont(font);
}
void TextBox::setSpacing(float space) {
	m_text.setSpacing(space);
}
std::string TextBox::getText() {
	return m_text.getContent();
}
void TextBox::changeTextColor(Color color) {
	m_text.changeColor(color);
}

//=================================================Color Function=======================================
void TextBox::setOutlineColor(Color color) {
	static_cast<BoxState*>(m_state.get())->setOutlineColor(color);
}
void TextBox::setBackgroundColor(Color color) {
	m_state->setMainColor(color);
}
void TextBox::changeBackgroundColor(Color color) {
	GUIAnimatingObject::changeColor(color);
}
Color TextBox::getOutlineColor() {
	return static_cast<BoxState*>(m_state.get())->getOutlineColor();
}
//=================================================Combine Funtion=======================================
//==========Timing Functioin=======================
void TextBox::setAnimationDuration(float time) {
		GUIAnimatingObject::setAnimationDuration(time);
		m_text.setAnimationDuration(time);
}
//====================position Function=======================

void TextBox::setPosition(Vector2 position) {
	m_text.setPosition(position);
	GUIAnimatingObject::setPosition(position);
}
void TextBox::moveToPosition(Vector2 newPos) {
	m_text.moveToPosition(newPos);
	GUIAnimatingObject::moveToPosition(newPos);
}

//=================================================Update===============================================
void TextBox::update() {
	m_text.update();
	GUIAnimatingObject::update();
}