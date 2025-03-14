#include "GUIText.h"
//Default constructor
GUIText::GUIText() :m_content(""), m_color(BLACK), m_font(), m_fontSize(20.0f), m_spacing(2.0f) {};

//Modify content

void GUIText::setFont(const Font font) {
	m_font = font;
}

void GUIText::setTextSize(const float size) {
	m_fontSize = size;
}

void GUIText::setTextColor(const Color color) {
	m_color = color;
}

void GUIText::setContent(const std::string text) {
	m_content = text;
}

void GUIText::setSpacing(const float space) {
	m_spacing = space;
}

//Get content

std::string GUIText::getContent() {
	return m_content;
}

float GUIText::getTextSize() {
	return m_fontSize;
}

void GUIText::update() {

}

void GUIText::render() {
	DrawTextEx(m_font, m_content.c_str(), m_pos, m_fontSize, m_spacing, m_color);
}