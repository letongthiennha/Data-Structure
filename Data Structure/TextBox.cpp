#include "TextBox.h"
//=============================================TextBox=============================================

TextBox::TextBox():m_thickness(1), m_outline_color(BLACK) {
	GUIAnimatingObject::setPosition({ 0,0 });
	m_text.setPosition({ 0,0 });
}
TextBox::TextBox(float x, float y, std::string text) {
	m_state = std::make_unique<GUIState>();
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
void TextBox::setThickness(int thickness) {
	m_thickness = thickness;
}

//=================================================Color Function=======================================
void TextBox::setOutlineColor(Color color) {
	m_outline_color = color;
}
void TextBox::setBackgroundColor(Color color) {
	GUIAnimatingObject::setMainColor(color);
}
void TextBox::changeBackgroundColor(Color color) {
	GUIAnimatingObject::changeColor(color);
}
Color TextBox::getOutlineColor() {
	return m_outline_color;
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
void TextBox::addStep() {
	m_text.addStep();
	GUIAnimatingObject::addStep();
}
//=================================================Update===============================================
void TextBox::update() {
	m_text.update();
	GUIAnimatingObject::update();
}