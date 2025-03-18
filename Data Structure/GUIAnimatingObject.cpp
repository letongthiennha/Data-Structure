#include "GUIAnimatingObject.h"
#include <math.h>
#include <algorithm> 

//==============Moving Function========================
void GUIAnimatingObject::setPosition(Vector2 position) {
	GUIObject::setPosition( position);
}

//Determine position to move to, called before adding Step
void GUIAnimatingObject::moveToPosition(Vector2 newPos) {
	if (m_MovingDuration == 0) {
		setPosition(newPos);
		return;
	}
	//Set new position
	m_targetState->setPosition(newPos);

	//State before moving
	Vector2 currentPos = m_state->getPosition();
	if (!m_animationQueue.empty())	currentPos = m_animationQueue.back()->getPosition();

	//Calculate distance
	float xDistance = m_targetState->getPosition().x - currentPos.x;
	float yDistance = m_targetState->getPosition().y - currentPos.y;
	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);


	//Moving distance in 1 frame is call moving speed,
	//In order to determine how far to travel in 1 frame to reach destination in duration time
	//We must calculate how many frame to reach that position and let the distance divide by that amount
	//Every frame is GetFrameTime() second and there is total m_duration time
	// So there is m_Moving duration/ getFrameTime() total FRAME
	float totalFrames = m_MovingDuration * defaultFPS;
	//Calculate how far to travel in a Frame by let total distance/Frame, we have the final formula
	m_MovingSpeed = totalDistance/totalFrames;
}

void GUIAnimatingObject::setMovingDuration(float time) {
	if (time <1e-3) m_MovingDuration = 0;
	else
	m_MovingDuration = time;
}
//Update position everyframe after calling adding step, Compare with the front element in the queue
void GUIAnimatingObject::update_position() {
	if (m_MovingDuration <= 0 || m_animationQueue.empty()) return;

	Vector2 currentPos = m_state->getPosition();
	Vector2 targetPos = m_animationQueue.front()->getPosition();

	float xDistance = targetPos.x - currentPos.x;
	float yDistance = targetPos.y - currentPos.y;
	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);

	if (totalDistance < 1e-3) {
		m_state->setPosition(targetPos);
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

//Determine color to change to, called before adding Step

void GUIAnimatingObject::changeColor(Color color) {
	if (m_ChangingColorDuration == 0) {
		m_state->setMainColor(color);
		return;
	}
	//Set new Color
	m_targetState->setMainColor(color);


	//State before moving
	Color currentColor = m_state->getMainColor();
	if (!m_animationQueue.empty())	currentColor = m_animationQueue.back()->getMainColor();

	float redDifference = (m_targetState->getMainColor().r - currentColor.r);
	float greenDifference = (m_targetState->getMainColor().g - currentColor.g);
	float blueDifference = (m_targetState->getMainColor().b - currentColor.b);
	float totalDifference = sqrt(pow(redDifference, 2) + pow(blueDifference, 2) + pow(greenDifference, 2));
	//Calculate total Frames to do animation
	int totalFrames = m_ChangingColorDuration * defaultFPS;
	m_ChangingColorSpeed = totalDifference / totalFrames;


}

void GUIAnimatingObject::setColoringDuration(float time){
	if (time < 1e-3) m_ChangingColorDuration = 0;
	else
		m_ChangingColorDuration = time;
}

//Update Color everyframe after calling adding step, Compare with the front element in the queue

void GUIAnimatingObject::update_color() {
	if (m_ChangingColorDuration <= 0) return;

	Color currentColor = m_state->getMainColor();
	Color nextColor = m_animationQueue.front()->getMainColor();

	 float redDifference = (nextColor.r - currentColor.r);
	 float greenDifference =(nextColor.g - currentColor.g);
	 float blueDifference = (nextColor.b - currentColor.b);
	 float totalDifference = sqrt(pow(redDifference, 2) + pow(blueDifference, 2) + pow(greenDifference, 2) );

	const float closeColor = 5.0f;

	if (totalDifference < closeColor) {
		// Snap to target color
		m_state->setMainColor(nextColor);
		deltaColor = { 0,0,0 };
		return;
	}

	// Calculatehow much to change in each frame
	deltaColor.x += m_ChangingColorSpeed * redDifference / totalDifference; ;
	deltaColor.y += m_ChangingColorSpeed * greenDifference / totalDifference;
	deltaColor.z += m_ChangingColorSpeed * blueDifference / totalDifference;

	//Cast to unsigned char
	unsigned char increaseRed = static_cast<unsigned char>((deltaColor.x));
	unsigned char increaseGreen = static_cast<unsigned char>(deltaColor.y);
	unsigned char increaseBlue = static_cast<unsigned char>((deltaColor.z));


	// Decrease the difference
	deltaColor.x -= increaseRed;
	deltaColor.y -= increaseGreen;
	deltaColor.z -= increaseBlue;

	// Update the state with the new color
	Color newColor = { currentColor.r + increaseRed, currentColor.g + increaseGreen, currentColor.b + increaseBlue, currentColor.a };
	m_state->setMainColor(newColor);
}


//===================Confirm Step=================
void GUIAnimatingObject::addStep() {
	m_historyQueue.push_front(std::make_unique<GUIState>(*m_state));
	m_animationQueue.push_back(std::make_unique<GUIState>(*m_targetState));
}

//===================Update Function==============
void GUIAnimatingObject::update() {
	//No step to display
	if (m_animationQueue.empty()) return;
	//Animation Done
	if (isSameColor(m_state->getMainColor() ,m_animationQueue.front()->getMainColor()) &&
		isSamePosition(m_state->getPosition(), m_animationQueue.front()->getPosition())) {
		//Pop the first element
		m_animationQueue.pop_front();
		deltaColor = { 0,0,0 };
		return;
	}
		update_color();
		update_position();
		m_targetState = std::make_unique<GUIState>(*m_state);
}

