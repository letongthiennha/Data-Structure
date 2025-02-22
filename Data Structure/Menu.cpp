#include "Menu.h"

void Menu::render(){
	for (auto &x : this->menu) {
		x.render();
	}
}