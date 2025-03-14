#include "GUIObject.h"

void GUIObject::setPosition(Vector2 position) {
	m_pos = position;
}

Vector2 GUIObject::getPosition() {
	return m_pos;
}