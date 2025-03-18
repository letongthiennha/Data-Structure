//#include "SLL.h"
//#include <string>
//#include "raylib.h"
//
////=============================Node===================================
//
//
////General Moving 
//	
//bool LinkedList::Node::moveToAPos(Vector2 newPos) {
//	float xDistance = newPos.x - pos.x;
//	float yDistance = newPos.y - pos.y;
//	float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);
//
//	if (totalDistance <= speed) {
//		pos = newPos;
//		return true;
//	}
//
//	// Calculate dynamic speed based on remaining distance
//	float dynamicSpeed = speed * (0.5f + 0.5f * (totalDistance / 100.0f)); // Adjust 100.0f for scaling
//	dynamicSpeed = fmax(dynamicSpeed, speed * 0.4f); // Min speed threshold
//	dynamicSpeed = fmin(dynamicSpeed, speed * 1.8f); // Max speed cap
//
//	// Normalize movement vector
//	float moveX = (xDistance / totalDistance) * dynamicSpeed;
//	float moveY = (yDistance / totalDistance) * dynamicSpeed;
//
//	// Update position
//	pos.x += moveX;
//	pos.y += moveY;
//
//	return false;
//}
//	
//
////Moving to the next position
//Vector2 LinkedList::Node::getNextPos() {
//	//Next position to the right
//	if (this->right && this->pos.x + dx + radius < GetRenderWidth()) return Vector2{ pos.x + dx, pos.y };
//	//Start a new line and go to the left
//	if (this->right && this->pos.x + dx + radius > GetRenderWidth()) {
//		right = false;
//		return Vector2{ pos.x, pos.y + dy };
//	}
//	//Go to the left
//	if (!this->right && this->pos.x - dx - radius > 0) return Vector2{ pos.x - dx,pos.y };
//	//Start a new line and go to the right
//	right = true;
//	return Vector2{ pos.x,pos.y + dy };
//}
//
////ADDING MOVING
//
//
//// Update
//void LinkedList::Node::update() {
//
//}
////Render
//void LinkedList::Node::render() {
//	std::string text = std::to_string(val);
//
//	int fontSize = 20;
//	int textWidth = MeasureText(text.c_str(), fontSize);
//	int textHeight = fontSize;
//
//	// Center
//	DrawCircle(pos.x, pos.y, radius, texture);
//	if (isHighlight)
//		DrawCircleLines(pos.x, pos.y, radius + 1, highlight);
//	DrawCircleLines(pos.x, pos.y, radius, outLineColor);
//	DrawText(text.c_str(), pos.x - textWidth / 2, pos.y - textHeight / 2, fontSize, BLACK);
//
//}   
//
//
//
////============================Linked List====================================
//
////Constructor Destructor
//LinkedList::LinkedList() {
//	dummy = new Node{ 0,nullptr };
//	nodeCount = 0;
//};
//LinkedList::~LinkedList() {
//	Node* curr = dummy->next;
//	while (curr) {
//		Node* del=curr;
//		curr = curr->next;
//		delete del;
//	}
//	delete dummy;
//}
//
//
//
////1.============Logic Function=================
//LinkedList::Node* LinkedList::push_back(int n) {
//	Node* curr = dummy;
//	while (curr && curr->next) curr = curr->next;
//
//	curr->next = new Node(n, nullptr);
//}
//
//
//void LinkedList::remove(int n){
//
//}
//
////2.==========Animation Function===============
//
//
////Render
//void LinkedList::render() {
//	Node* curr = dummy->next;
//
//	while (curr) {
//		curr->render(); 
//		curr = curr->next;
//	}
//}