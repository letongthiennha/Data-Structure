#pragma once
#define defaultFPS 60

#include "raylib.h"
#include "GUIObject.h"
#include "queue"

inline bool isSameColor(Color c1, Color c2) {
	return (c1.r == c2.r) &&
		(c1.g == c2.g) &&
		(c1.b == c2.b) &&
		(c1.a == c2.a);
}
inline bool isSamePosition(Vector2 v1, Vector2 v2) {
	return (v1.x == v2.x) && (v1.y == v2.y);
}
//Abstract Class For any Animating Object, Update state step by step after 1 Frame
class GUIAnimatingObject: public GUIObject {
protected:
	//=================State Control=================
	//Helper Pointer to determine next	state
	std::unique_ptr<GUIState>m_targetState = std::make_unique<GUIState>(*m_state);


	//================Flow Control==============
	
	//History queue for undo features
	std::deque<std::unique_ptr<GUIState>>	m_historyQueue;

	//Target Status
	std::deque<std::unique_ptr<GUIState>>	m_animationQueue;

	//Future for redo features
	std::deque<std::unique_ptr<GUIState>>	m_futureQueue;


	//=======================Animation Control======================
	
	//Change Color Status
	float			m_ChangingColorDuration,
					m_ChangingColorSpeed;
	Vector3			deltaColor;
	//Moving Status
	float			m_MovingDuration,
					m_MovingSpeed;





public:

	//Moving Function
	virtual void		setPosition(Vector2 position) override,
						//After Use This Function, must confirm Step to do it
						moveToPosition(Vector2 newPos),	//Move Slowly

						setMovingDuration(float time);		//Set Duration of animation

	//Change Color Function
	virtual void		setMainColor(Color color) override,
						//After Use This Function, must confirm Step to do it

						changeColor(Color color),

						setColoringDuration(float time);

	//Update after 1 frame
	virtual void		update_position(),
						update_color(),
						update(),
	
	//Render frame
						render() override =0;


	virtual				~GUIAnimatingObject() = default;


	//=======================Confirm Step============================

	virtual void		addStep();
	GUIAnimatingObject()
		: m_ChangingColorDuration(1.0f),
		m_MovingDuration(1.0f),
		m_MovingSpeed(1.0f) {
		m_state = std::make_unique<GUIState>();
	}
};