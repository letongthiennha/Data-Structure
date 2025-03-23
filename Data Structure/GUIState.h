#pragma once

#include "raylib.h"
//Every object render on screen
class GUIState {
protected:
	Vector2 m_pos;
	Color m_main_color;
public:
	GUIState() :m_pos{ -100,-100 },m_main_color(BLACK) {};

	GUIState(const GUIState& other) {
		this->m_pos = other.m_pos;
		this->m_main_color = other.m_main_color;
	}
	//Set And Get Position
	Vector2				getPosition();
	virtual void		setPosition(Vector2 position);

	//Set And Get Color
	Color				getMainColor();
	virtual void		setMainColor(Color color);


	virtual				~GUIState()=default;
};

 