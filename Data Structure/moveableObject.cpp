#include "movableObject.h"
#include <math.h>


//Moving Function
void movableObject::setPosition(Vector2 position) {
	GUIObject::setPosition( position);
}

void movableObject::moveToPosition(Vector2 newPos) {
	if (m_duration == 0) {
		setPosition(newPos);
		return;
	}

	m_targetPos= newPos;

	float xDistance = m_targetPos.x - m_currPos.x;
	float yDistance = m_targetPos.y - m_currPos.y;
	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);

	m_speed = totalDistance / m_duration;
}

void movableObject::setDuration(float time) {
	if (time <= 0) m_duration = 0;
	else
	m_duration = time;
}

void movableObject::update() {
	if (m_currPos.x == m_targetPos.x && m_currPos.y == m_targetPos.y) return;

	float xDistance = m_targetPos.x - m_currPos.x;
	float yDistance = m_targetPos.y - m_currPos.y;
	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);

	if (totalDistance <= m_speed) {
		m_currPos = m_targetPos;
		return;
	}
	float xSpeed = (xDistance / totalDistance) * m_speed;
	float ySpeed = (yDistance / totalDistance) * m_speed;

	//Move x and move y
	m_currPos.x += xSpeed;
	m_currPos.y += ySpeed;

	//If it pass the target, snap it back
	if ((xDistance > 0 && m_currPos.x > m_targetPos.x) || (xDistance < 0 && m_currPos.x < m_targetPos.x))
		m_currPos.x = m_targetPos.x;
	if ((yDistance > 0 && m_currPos.y > m_targetPos.y) || (yDistance < 0 && m_currPos.y < m_targetPos.y))
		m_currPos.y = m_targetPos.y;
}