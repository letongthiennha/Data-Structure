#include "GUIAnimatingObject.h"
#include <math.h>
#include <algorithm> 
//====Timing Function=======================

//Set Time For The next Instruction
void GUIAnimatingObject::setAnimationDuration(float time) {
	m_buildingInstruction.time = time;
}

//==============Moving Function========================
void GUIAnimatingObject::setPosition(Vector2 position) {
	m_state->setPosition(position);
	m_targetState->setPosition(position);
}

//Determine position to move to, called before adding Step
void GUIAnimatingObject::moveToPosition(Vector2 newPos) {

	//Set new position
	m_targetState->setPosition(newPos);


}

//Update position everyframe after calling adding step, Compare with the front element in the queue
void GUIAnimatingObject::update_position() {
	if ( m_animationQueue.empty()) return;
	//Instant moving when only set position
	if (m_animationQueue.front().time == 0) {
		m_state->setPosition(m_animationQueue.front().m_targetState->getPosition());
		return;
	}
	//Calculate the left frame
	float deltaTime = m_animationQueue.front().time - m_animationTime;
	int totalFrame = defaultFPS *deltaTime;

	//Create 2 Name For the vector
	Vector2 currentPos = m_state->getPosition();
	Vector2 targetPos = m_animationQueue.front().m_targetState->getPosition();

	//Calculate the distance
	float xDistance = targetPos.x - currentPos.x;
	float yDistance = targetPos.y - currentPos.y;
	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);
	//Only initiliaze speed when the first frame
	if (m_animationTime == 0) m_MovingSpeed = totalDistance / totalFrame;
	//if it is close snap it
	if (totalDistance < 1e-3) {
		m_state->setPosition(targetPos);
		return;
	}


	//Calculate how much to move in each frame
	float dx = (m_MovingSpeed * xDistance) / totalDistance;
	float dy = (m_MovingSpeed * yDistance) / totalDistance;

	// Create an update position after adding how muc to move
	Vector2 newPos = { currentPos.x + dx, currentPos.y + dy };

	// If move pass then snap back
	if ((dx > 0 && newPos.x > targetPos.x) || (dx < 0 && newPos.x < targetPos.x))
		newPos.x = targetPos.x;
	if ((dy > 0 && newPos.y > targetPos.y) || (dy < 0 && newPos.y < targetPos.y))
		newPos.y = targetPos.y;

	m_state->setPosition(newPos);

}


//====================Coloring Function=================
void GUIAnimatingObject::setMainColor(Color color) {
	m_state->setMainColor(color);
	m_targetState->setMainColor(color);
}

//Determine color to change to, called before adding Step

void GUIAnimatingObject::changeColor(Color color) {

	//Set new Color
	m_targetState->setMainColor(color);
}


//Update Color everyframe after calling adding step, Compare with the front element in the queue

void GUIAnimatingObject::update_color() {
	if (m_animationQueue.empty()) return;
	if (m_animationQueue.front().time == 0) {
		m_state->setMainColor(m_animationQueue.front().m_targetState->getMainColor());
		return;
	}
	float deltaTime = m_animationQueue.front().time - m_animationTime;
	int totalFrame = defaultFPS * deltaTime;

	Color currentColor = m_state->getMainColor();
	Color nextColor = m_animationQueue.front().m_targetState->getMainColor();

	 float redDifference = (nextColor.r - currentColor.r);
	 float greenDifference =(nextColor.g - currentColor.g);
	 float blueDifference = (nextColor.b - currentColor.b);
	 float totalDifference = sqrt(pow(redDifference, 2) + pow(blueDifference, 2) + pow(greenDifference, 2) );

	const float closeColor = 5.0f;
	if(m_animationTime==0) m_ChangingColorSpeed = totalDifference / totalFrame;
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
		m_buildingInstruction.m_targetState = std::move(m_targetState);
		m_historyQueue.push_front(instruction(m_buildingInstruction));
		m_animationQueue.push_back(instruction(m_buildingInstruction));
		m_targetState = std::make_unique<GUIState>(*m_animationQueue.back().m_targetState);
		m_buildingInstruction = instruction();
}

bool GUIAnimatingObject::isAnimationDone() {
	return isSameState(std::make_unique<GUIState>(*m_state), std::make_unique<GUIState>(*m_animationQueue.front().m_targetState));
}

//===================Update Function==============
void GUIAnimatingObject::update() {
	//No step to display
	if (m_animationQueue.empty()) return;
	//Animation Done
	if (isAnimationDone()) {
		//Pop the first element
		m_animationTime =0;
		m_animationQueue.pop_front();
		deltaColor = { 0,0,0 };
		return;
	}

		update_color();
		update_position();
		m_animationTime += 1.0f / defaultFPS;
		m_targetState = std::make_unique<GUIState>(*m_state);
}

