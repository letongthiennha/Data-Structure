#pragma once
#include "Button.h"
#include "Setting.h"
#include "TextBox.h"

class ShPController {
public:
	ShPController();
	~ShPController();
	bool isRandomClicked() const;
	bool isInputClicked() const;
	bool isDijkstraClicked() const;
	bool isLoadFileClicked() const;
	bool isEditClicked() const;
	int getStartVertex();
	virtual void update();
	virtual void render();

protected:
	Button Random;
	Button Input;
	Button Dijkstra;
	Button LoadFile;
	Button Edit;
	TextBox startVertexTextBox;
	Rectangle OperationBoard;
}; 
