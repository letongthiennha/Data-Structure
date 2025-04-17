#include "Slider.h"
#include <string>
Slider::Slider() {
	m_progress = 0.5f;
	m_sliderBound = { 0,0,0,0 };
	m_slider = { 0,0,0,0 };
	m_slider.width = 60;
	m_slider.height = 60;
}
void Slider::setSize(Vector2 size) {
	m_sliderBound.width = size.x;
	m_sliderBound.height = size.y;
	m_slider.x = m_sliderBound.x;
	m_slider.y = m_sliderBound.y+m_sliderBound.height/2;

}
void Slider::setPosition(Vector2 position) {
	m_sliderBound.x = position.x;
	m_sliderBound.y = position.y;
	m_slider.x = m_sliderBound.x ;
	m_slider.y = m_sliderBound.y + m_sliderBound.height / 2;
}
void Slider::setProgress(float progress) {
	m_progress = progress;

}
float Slider::getProgress() const {
	return m_progress*2;
}
void Slider::update() {
	Vector2 mousePos = GetMousePosition();
	if (CheckCollisionPointRec(mousePos, m_slider) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		float length = m_sliderBound.height;
		float mouseY = mousePos.y - m_sliderBound.y;
		m_progress = mouseY / length;
		if (m_progress < 0.0f) m_progress = 0.0f;
		if (m_progress > 1.0f) m_progress = 1.0f;
	}
	m_slider.y = m_sliderBound.y + m_sliderBound.height * m_progress - m_slider.height / 2+10;

}
void Slider::render() {
	Rectangle renderSlider = m_slider;
	renderSlider.height = 20;
	renderSlider.width = 30;
	DrawRectangleRec(m_sliderBound, LIGHTGRAY);
	DrawRectangleRec(renderSlider, DARKGRAY);
	std::string text ="Speed: X" +std::to_string(getProgress()).substr(0, 4);
	DrawText(text.c_str(), m_sliderBound.x + 10, m_sliderBound.y - 20, 20, BLACK);
}