#include "SLL.h"
#include <string>
//Moving A Node

//Node Render
void LinkedList::Node::render() {
	if (!isRender) return;
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

//Operation 

void LinkedList::push_back(int n) {
	pTail->isRender = true;
	pTail->unHighlight();

	Node* nextNode = new Node(n, nullptr);
	if (pTail == dummy) nextNode->pos.x = 100.0f;
	else nextNode->pos.x = pTail->pos.x + dx;
	nextNode->pos.y = 100.0f;
	isAdding = true;
	nextNode->isRender = false;//Wait until complete animation to render the node

	pTail->next = nextNode;
	pTail = pTail->next;
}
//void LinkedList::remove(int n){
//	isRemoving = true;
//	Node* curr = dummy->next;
//	while (curr->next) {
//		if (curr->next->val == n) {
//			prev = curr;          
//			removeNode = curr->next; 
//			next = removeNode->next;
//			break;
//		}
//		curr = curr->next;
//	}
//	next = removeNode->next;
//}
//Animation
void LinkedList::updateForAdding() {
	static Node* curr = nullptr; // To highlight
	static Node* prev = nullptr; // to unhighlight
	static int frameCounter = 0; // Controls the animation speed


		if (!curr) {
			curr = dummy->next;
			prev = dummy;
		}

		frameCounter++;

		if (frameCounter >= 0.5f * GetFPS()) {//After 0
			if (curr) {
				if (prev) prev->unHighlight();
				curr->setHighlight();

				prev = curr;
				curr = curr->next;
			}

			frameCounter = 0; // Reset frame counter

			// Reach the end, stop highlighting
			if (!curr) {
				pTail->isRender = true; // Show the newly added node
				isAdding = false;       // Stop animation
				curr = nullptr;
				prev = nullptr;
			}
	}
}
void LinkedList::updateForRemoving() {
	if (!removeNode) return;

	//Count Frame

	static const float timeUpdate = 1.0f / 60;
	static float time = 0;
	time += GetFrameTime();
	if (time >= timeUpdate) {
		//Animation move down curr Node each state
		const float speed = 4.0f / 3; //Speed Move Down
		static const float deletePos = removeNode->pos.y + 80.0f;
		if (removeNode->pos.y < deletePos) {
			removeNode->pos.y += speed;
		}
		else {
				delete removeNode;
				removeNode = nullptr;
				prev->next = next;
				prev = nullptr;
				next = nullptr;
				isRemoving = false;
			}
		time -= timeUpdate;
	} 
	if (!isRemoving) time = 0;
}

//Update Position for Operation

void LinkedList::update() {
	if (isAdding) updateForAdding();
	if (isRemoving) updateForRemoving();
}

//Render
void LinkedList::render() {
	Node* curr = dummy->next;

	while (curr) {
		if(curr->next&&curr->next->isRender)
		DrawLine(curr->pos.x, curr->pos.y, curr->next->pos.x, curr->next->pos.y, GRAY);
		curr->render(); 
		curr = curr->next;
	}
}