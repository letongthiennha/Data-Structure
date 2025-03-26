//#include "GUIText.h"
////==================Text State=======================
////Constructor
//GUIText::GUIText() {
//	m_font = GetFontDefault();
//	m_content = "";
//	m_fontSize = 20;
//	m_spacing = 2;
//}
//
//
////Modify content
//
//void GUIText::setFont( Font font) {
//	m_font = font;
//}
//
//void GUIText::setTextSize(const float size) {
//	if (size <= 0) m_fontSize = 1;
//	m_fontSize = size;
//}
//
//void GUIText::setTextColor(const Color color) {
//	setMainColor ( color);
//}
//
//void GUIText::setContent(const std::string text) {
//	m_content = text;
//}
//
//void GUIText::setSpacing(const float space) {
//	m_spacing = space;
//}
//
////Get content
//
//std::string GUIText::getContent() {
//	return m_content;
//}
//
//float GUIText::getTextSize() {
//	return m_fontSize;
//}
//
//Font GUIText::getTextFont() {
//	return m_font;
//}	
//
//float GUIText::getSpacing() {
//	return m_spacing;
//}
////Update for 1 frame
//void GUIText::update() {
//	GUIAnimatingObject::update();
//}
//
//
////Draw Function
//void GUIText::render() {
//	DrawTextEx(m_font, m_content.c_str(), m_state->getPosition(), m_fontSize, m_fontSize, m_state->getMainColor());
//}