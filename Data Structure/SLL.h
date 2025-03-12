#pragma once
#include "GUIObject.h"
#include <string>
#include <deque>

class LinkedList {
private:
	static constexpr float dx = 80.0f;
	static constexpr float dy = 100.0f;
	class Node:public GUIObject {
	private:
		//Properties
		Color highlight = RED;
		Color texture = YELLOW;
		Color outLineColor = BLACK;
		const float radius = 30;
		
		//Speed
		const float speed = 5.0f;
		//Direction
		bool right = true;
		//Operation
		bool isHighlight = false;
	public:
		int val;
		Node* next;

		//Constructor
		Node(int n, Node* next) : val(n), next(next) {};

		float getRadius() { return radius; }



		//Highlight
		void setHighlight() { isHighlight = true; }
		void unHighlight() { isHighlight = false; }


		//General Animation
		Vector2 targetPos;
		bool moveToAPos(Vector2 newPos);

		//Moving 

		Vector2 getNextPos();

		//Render
		void update();
		void render() override;
	};
	Node* dummy;


	
public:	
//Get and set

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