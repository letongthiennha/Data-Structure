#pragma once

#include "Button.h"

class ControllerBoard {
public:
	ControllerBoard();
	 ~ControllerBoard();

	bool isHomeClicked() const;
	bool isBeginClicked() const;
	bool isResumeClicked() const;
	bool isNextClicked() const;
	bool isPrevClicked() const;
	bool isEndClicked() const;

	virtual void update();
	virtual void render();
protected:
	Button Home;
	//State  Controller
	Button Begin;
	Button Resume;
	Button Next;
	Button Prev;
	Button End;

	Rectangle OperationBoard;
};