#pragma once
#include "raylib.h"
class Slider {
private: 
	float m_progress;
	Rectangle m_sliderBound;
	Rectangle m_slider;
public:
	Slider();
	void setSize(Vector2 size);
	void setPosition(Vector2 position);
	void setProgress(float progress);
	float getProgress()const;
	void update();
	void render();
};