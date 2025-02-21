#pragma once
#include "GUIObject.h"
#include <string>
class LinkedList {
private:
	class Node:public GUIObject {
	private:
		Color highlight = RED;
		Color texture = YELLOW;
		Color outLineColor = BLACK;
		bool isHighlight = false;
	public:
		int val;
		Node* next;
		//Render
		const float radius = 30;
		void setHighlight() { isHighlight = true; }
		void unHighlight() { isHighlight = false; }
		//Constructor
		Node(int n, Node* next) : val(n), next(next) {};

		void render() override;
	};
	const float dx = 80.0f;
	Node* dummy;
	Node* pTail;

	//Animation
	bool highlightOneByOneToTheEnd();

public:
//Constructor and destructor
	LinkedList();
	~LinkedList();

//Function to add or remove
	void push_back(int n);
	void remove(Node* &curr);

//Function for GUI
	void update();
	void render();
};