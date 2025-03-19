#include "ListNode.h"
//=============================================ListNode=============================================
ListNode::ListNode() {
	m_val = 0;
	m_radius = 20;
	m_next = nullptr;
}
//=================================================Value Function=======================================
void ListNode::setVal(int val) {
	m_val = val;
	m_text.setContent(std::to_string(val));
}
int ListNode::getVal() {
	return m_val;
}
void ListNode::setNext(ListNode* next) {
	m_next = next;
}
ListNode* ListNode::getNext() {
	return m_next;
}
//=================================================Position Function=======================================
void ListNode::setPosition(Vector2 position) {
	TextBox::setPosition(position);
}
void ListNode::moveToPosition(Vector2 newPos) {
	TextBox::moveToPosition(newPos);
}
//==============================================Size Function=========================================
void ListNode::setRadius(float radius) {
	m_radius = radius;
}
//=================================================Render Function=======================================
void ListNode::render() {
	//Draw Circle
	DrawCircle(m_state->getPosition().x, m_state->getPosition().y, m_radius, m_state->getMainColor());
	DrawCircleLines(m_state->getPosition().x, m_state->getPosition().y, m_radius, BLACK);
	//Draw Text
	m_text.render();
}
