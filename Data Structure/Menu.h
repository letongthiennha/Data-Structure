#pragma once
#include "Button.h"
#include <vector>
class Menu:GUIObject {
private:
	std::vector<Button> menu{
	};
public:
	Menu() = default;
	~Menu() = default;
	void render() override;
};