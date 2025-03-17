#include "GUIObject.h"

GUIObject::GUIObject() : m_state(std::make_unique<GUIState>()) {
	m_state->setMainColor(BLACK);
	m_state->setPosition(Vector2{ 0, 0 });
};
GUIObject::GUIObject(std::unique_ptr<GUIState> state) : m_state(std::move(state)) {};


//Set and Get Function
Vector2 GUIObject::getPosition() {
	return m_state->getPosition();
}

void GUIObject::setPosition(Vector2 position) {
	m_state->setPosition(position);
}

void GUIObject::setMainColor(Color color) {
	m_state->setMainColor(color);
}