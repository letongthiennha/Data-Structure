#pragma once

#include "raylib.h"
#include "GUIObject.h"
#include "queue"
//Abstract Class For any Animating Object
class GUIAnimatingObject: public GUIObject {
protected:
	//History queue
	std::deque<std::unique_ptr<GUIState>> history;
	//Target Status
	std::unique_ptr<GUIState> m_targetState;
	

	//Change Color Status
	float			m_ChangingColorDuration;
	//Moving Status
	float			m_MovingDuration,
					m_MovingSpeed;
	GUIAnimatingObject() = default;// No direct initialzation
public:

	//Moving Function
	void virtual	setPosition(Vector2 position) override,

					moveToPosition(Vector2 newPos),	//Move Slowly

					setMovingDuration(float time);		//Set Duration of animation

	//Change Color Function
	void virtual	changeColor(Color color),

					setColoringDuration(float time);

	//Update after 1 frame
	virtual void	update(),
	
	//Render frame
					render() override =0;


	virtual			~GUIAnimatingObject() = default;
};