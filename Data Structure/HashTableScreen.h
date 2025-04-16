#pragma once
#include "Button.h"
class HashTableScreen
{
private:
	Button Home;
public:
	HashTableScreen();
	bool goBack();

	void renderList();
	void update();
};

