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

		//Determine whether to render or not
		bool isRender = true;
		void render() override;
	};
	const float dx = 80.0f;
	Node* dummy;
	Node* pTail;

	//Adding State
	bool isAdding = false;
	//Removing State
	bool isRemoving = false;
	Node* removeNode = nullptr;
	Node* prev = nullptr;
	Node* next = nullptr;
	//Animation
	void updateForAdding();
	void updateForRemoving();
public:
//Constructor and destructor
	LinkedList();
	~LinkedList();

//Function to add or remove
	void push_back(int n);
	void remove(int n);

//Function for GUI
	void update();
	void render();
};