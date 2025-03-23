#pragma once
#include "GUIState.h"
#include "memory"
class GUIObject{
protected:
	std::unique_ptr<GUIState>	m_state;
	bool isVisible=true;
public:
	//Constructor
	GUIObject();
	GUIObject(std::unique_ptr<GUIState> state);

	Vector2						getPosition();

	virtual void				setPosition(Vector2 position);
	virtual void				setMainColor(Color color);

	//Draw function
	virtual void				render()=0;

	// Destructor
	virtual						~GUIObject() = default;
};


