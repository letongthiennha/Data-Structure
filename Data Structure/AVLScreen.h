#pragma once
#include "Button.h"
class AVLScreen
{
private:
	Button Home;
public:
	AVLScreen();
	bool goBack();
	void renderList();
	void update();
};
