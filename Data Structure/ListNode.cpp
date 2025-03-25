//#include "ListNode.h"
//#include "Font.h"
////=============================================ListNode=============================================
//ListNode::ListNode() {
//	m_val = 0;
//	m_radius = 30;
//	m_thickness = 3;
//	m_next = nullptr;
//	m_text.setPosition(computeTextPosition(m_state->getPosition()));
//	m_text.setFont(arial);
//}
//ListNode::ListNode(Vector2 startPos, Color mainColor, int val) {
//	this->setVal(val);
//	m_state->setMainColor(mainColor);
//	m_state->setPosition(startPos);
//	m_targetState = std::make_unique<GUIState>(*m_state);
//	m_radius = 30;
//	m_thickness = 3;
//	m_next = nullptr;
//	m_text.setPosition(computeTextPosition(startPos));
//	m_text.setFont(arial);
//}
////=================================================Value Function=======================================
//void ListNode::setVal(int val) {
//	m_val = val;
//	m_text.setContent(std::to_string(val));
//}
//int ListNode::getVal() {
//	return m_val;
//}
//void ListNode::setNext(ListNode* next) {
//	m_next = next;
//}
//ListNode* ListNode::getNext() {
//	return m_next;
//}
////=================================================Position Function=======================================
//void ListNode::setPosition(Vector2 position) {
//	TextBox::setPosition(position);
//	m_text.setPosition(computeTextPosition(position));
//}
//void ListNode::moveToPosition(Vector2 newPos) {
//	TextBox::moveToPosition(newPos);
//	m_text.moveToPosition(computeTextPosition(newPos));
//}
//Vector2 ListNode::computeTextPosition(Vector2 position) {
//	Vector2 textSize = MeasureTextEx(arial, m_text.getContent().c_str(), m_text.getTextSize(), m_text.getSpacing());
//	float x = position.x-textSize.x/2;
//	float y = position.y - textSize.y / 2;
//	return Vector2{ x, y };
//}
////==============================================Size Function=========================================
//void ListNode::setRadius(float radius) {
//	m_radius = radius;
//}
//
////=================================================Render Function=======================================
//void ListNode::render() {
//	//Draw Circle
//	DrawCircle(ceil(m_state->getPosition().x), ceil(m_state->getPosition().y), m_radius+m_thickness*3/4, m_state->getMainColor());
//	DrawRing(m_state->getPosition(), m_radius, m_radius + m_thickness, 0, 360, 30, m_outline_color);
//	//Draw Text
//	m_text.render();
//}
////=============================================ListNode=============================================
