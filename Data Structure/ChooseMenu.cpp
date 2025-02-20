#include "ChooseMenu.h"

void ChooseMenu::render(){
	for (auto &x : this->menu) {
		x.render();
	}
}