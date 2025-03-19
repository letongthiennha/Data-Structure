#pragma once

#include "TextBox.h"

class ListNode :public TextBox {
private:
	int m_val;
	float m_radius;
	ListNode* m_next;
public:	
	ListNode();
	//=================================================Value Function=======================================
	void setVal(int val);
	int getVal();
	void setNext(ListNode* next);
	ListNode* getNext();
	//==============================================Size Function=========================================
	void setRadius(float radius);
	//=================================================Position Function=======================================
	void setPosition(Vector2 position) override;
	void moveToPosition(Vector2 newPos) override;
	//=================================================Render Function=======================================
	virtual void render() override;
};
