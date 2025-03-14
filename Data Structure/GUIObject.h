#pragma once

#include "raylib.h"
//Every object render on screen
class GUIObject {
protected:
	Vector2 m_pos;
public:
	GUIObject() :m_pos{ 0,0 } {};

	//Render and update
	virtual void		update()=0,
						render()=0;

	//Set And Get Position
	Vector2				getPosition();
	virtual void				setPosition(Vector2 position);


	virtual				~GUIObject()=default;
};

 