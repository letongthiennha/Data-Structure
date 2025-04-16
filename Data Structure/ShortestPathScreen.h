#pragma once
#include "Button.h"
class ShortestPathScreen
{
private:
	Button Home;
public:
	ShortestPathScreen();
	bool goBack();

	void renderList();
	void update();
};

