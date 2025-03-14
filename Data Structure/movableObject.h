#pragma once

#include "raylib.h"
#include "GUIObject.h"

class movableObject: public GUIObject {
protected:
	Vector2			&m_currPos=m_pos;
	Vector2			m_targetPos;

	float			m_duration,
					m_speed;
	movableObject() = default;// No direct initialzation
public:

	//Moving Function
	void virtual	setPosition(Vector2 position) override,

					moveToPosition(Vector2 newPos),	//Move Slowly

					setDuration(float time),		//Set Duration of animation

					update();						//Update the object after every call

	virtual			~movableObject() = default;
};