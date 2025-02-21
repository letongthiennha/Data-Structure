#include "SLL.h"
#include <string>
const float DELTA_TIME = 1.0f / 24;
bool isAdding = false;
//Node Render
void LinkedList::Node::render() {
	std::string text = std::to_string(val);

	int fontSize = 20;
	int textWidth = MeasureText(text.c_str(), fontSize);
	int textHeight = fontSize;

	// Center
	DrawCircle(pos.x, pos.y, radius, texture);
	if (isHighlight)
		DrawCircleLines(pos.x, pos.y, radius + 1, highlight);
	DrawCircleLines(pos.x, pos.y, radius, outLineColor);
	DrawText(text.c_str(), pos.x - textWidth / 2, pos.y - textHeight / 2, fontSize, BLACK);

}

//Constructor Destructor
LinkedList::LinkedList() {
	dummy = new Node{ 0,nullptr };
	pTail = dummy;
};
LinkedList::~LinkedList() {
	Node* curr = dummy->next;
	while (curr) {
		Node* del=curr;
		curr = curr->next;
		delete del;
	}
	delete dummy;
}
//Animation
//bool LinkedList::highlightOneByOneToTheEnd() {
//	static Node* curr = dummy->next;
//	static Node* prev = dummy;
//	//Set Highlight
//	if (prev) {//Still Node left to highlight
//		curr->setHighlight();
//		prev->unHighlight();
//		if (curr);
//		curr = curr->next;
//		prev = prev->next;
//		return false;
//	}
//	else{//Out of left Node reset
//		curr = dummy->next;
//		prev = dummy;
//		return true;
//	}
//}
//Operation 

void LinkedList::push_back(int n) {
	Node* nextNode = new Node(n, nullptr);
	if (pTail == dummy) nextNode->pos.x = 100.0f;
	else nextNode->pos.x = pTail->pos.x + dx;
	nextNode->pos.y = 100.0f;
	pTail->next = nextNode;
	pTail = pTail->next;
}
void LinkedList::remove(Node* &curr){
	Node* prev = dummy;
	while (prev&&prev->next!=curr) {
		prev = prev->next;
	}
	prev->next = curr->next;
	while (prev && prev->next) prev=prev->next;
	pTail = prev;
	delete curr;
	curr = nullptr;
}


//Update Position for Operation
//void LinkedList::update() {
//	if (highlightOneByOneToTheEnd()) {
//		push_back(500);
//		pTail->setHighlight();
//	}
//}
//Render
void LinkedList::render() {
	update();
	Node* curr = dummy->next;
	while (curr) {
		curr->render();
		curr = curr->next;
	}
}