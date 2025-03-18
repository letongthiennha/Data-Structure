#include "GUIAnimatingObject.h"
#include <math.h>


//==============Moving Function========================
void GUIAnimatingObject::setPosition(Vector2 position) {
	GUIObject::setPosition( position);
}

void GUIAnimatingObject::moveToPosition(Vector2 newPos) {
	if (m_MovingDuration == 0) {
		setPosition(newPos);
		return;
	}
	//Set new position
	m_targetState->setPosition(newPos);

	//Calculate distance
	float xDistance = m_animationQueue.back()->getPosition().x - m_state->getPosition().x;
	float yDistance = m_animationQueue.back()->getPosition().y - m_state->getPosition().y;
	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);


	//Moving distance in 1 frame is call moving speed,
	//In order to determine how far to travel in 1 frame to reach destination in duration time
	//We must calculate how many frame to reach that position and let the distance divide by that amount
	//Every frame is GetFrameTime() second and there is total m_duration time
	// So there is m_Moving duration/ getFrameTime() total FRAME
	float totalFrames = m_MovingDuration / GetFrameTime();
	//Calculate how far to travel in a Frame by let total distance/Frame, we have the final formula
	m_MovingSpeed = totalDistance / totalFrames;
}

void GUIAnimatingObject::setMovingDuration(float time) {
	if (time <1e-3) m_MovingDuration = 0;
	else
	m_MovingDuration = time;
}

void GUIAnimatingObject::update_position() {
	if (m_MovingDuration <= 0 || m_animationQueue.empty()) return;

	Vector2 currentPos = m_state->getPosition();
	Vector2 targetPos = m_animationQueue.front()->getPosition();

	float xDistance = targetPos.x - currentPos.x;
	float yDistance = targetPos.y - currentPos.y;
	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);

	if (totalDistance < 1e-3) {
		m_state->setPosition(targetPos);
		m_animationQueue.pop_front();
		return;
	}

	// Normalize direction vector
	float dx = (m_MovingSpeed * xDistance) / totalDistance;
	float dy = (m_MovingSpeed * yDistance) / totalDistance;

	// Update position
	Vector2 newPos = { currentPos.x + dx, currentPos.y + dy };

	// If pass then snap back
	if ((dx > 0 && newPos.x > targetPos.x) || (dx < 0 && newPos.x < targetPos.x))
		newPos.x = targetPos.x;
	if ((dy > 0 && newPos.y > targetPos.y) || (dy < 0 && newPos.y < targetPos.y))
		newPos.y = targetPos.y;

	m_state->setPosition(newPos);

}


//====================Coloring Function=================
void GUIAnimatingObject::setMainColor(Color color) {
	GUIObject::setMainColor(color);
}

void GUIAnimatingObject::changeColor(Color color) {
	if (m_ChangingColorDuration == 0) {
		m_state->setMainColor(color);
		return;
	}
	//Set new Color
	m_targetState->setMainColor(color);
	
}

void GUIAnimatingObject::setColoringDuration(float time){
	if (time < 1e-3) m_ChangingColorDuration = 0;
	else
		m_ChangingColorDuration = time;
}

void GUIAnimatingObject::update_color() {
	if (m_ChangingColorDuration <= 0) return;

	Color currentColor = m_state->getMainColor();
	Color targetColor = m_animationQueue.front()->getMainColor();

	float step = GetFrameTime() / m_ChangingColorDuration;

	// Changing color slowly
	currentColor.r += (targetColor.r - currentColor.r) * step;
	currentColor.g += (targetColor.g - currentColor.g) * step;
	currentColor.b += (targetColor.b - currentColor.b) * step;
	currentColor.a += (targetColor.a - currentColor.a) * step;

	//Snap to the color
	if (abs(currentColor.r - targetColor.r) < 2 &&
		abs(currentColor.g - targetColor.g) < 2 &&
		abs(currentColor.b - targetColor.b) < 2 &&
		abs(currentColor.a - targetColor.a) < 2) {
		currentColor = targetColor;
	}

	// Update the state with the new color
	m_state->setMainColor(currentColor);
}


//===================Confirm Step=================
void GUIAnimatingObject::addStep() {
	m_historyQueue.push_front(std::make_unique<GUIState>(*m_state));
	m_animationQueue.push_back(m_targetState);
}

//===================Update Function==============
void GUIAnimatingObject::update() {
	//No step to display
	if (m_animationQueue.empty()) return;
	//Animation Done
	if (isSameColor(m_state->getMainColor() ,m_animationQueue.back()->getMainColor()) &&
		isSamePosition(m_state->getPosition(), m_animationQueue.back()->getPosition())) {
		m_animationQueue.pop_front();
		return;
	}
	update_color();
	update_position();
}
