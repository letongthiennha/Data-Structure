#pragma once
#include "Button.h"
#include <vector>
class ChooseMenu:GUIObject {
private:
	std::vector<Button> menu{
	};
public:
	ChooseMenu() = default;
	~ChooseMenu() = default;
	void render() override;
};