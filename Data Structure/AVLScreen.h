#pragma once
#include "Button.h"
class AVLScreen
{
private:
	Button Home;
public:
	AVLScreen();
	bool goBack();
	void render();
	void update();
};
