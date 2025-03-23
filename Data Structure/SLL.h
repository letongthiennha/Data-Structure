#pragma once	
#include "vector"
#include "ListNode.h"
class SLL{
private:
	//=======================Property=================
	std::vector<ListNode*> m_list;
	float distanceBetweenNode;
	Color m_mainBackgroundColor;
	Color m_textColor;
	Color m_highlightBackgroundColor;
	Color m_highLightTextColor;
	float m_animationDuration;
	//===================Calculate Position====================
	Vector2 startPostion;

	Vector2 positionAtIndex(int index);
	//===================Animation Helper=============
	void moveRightAllAfter(int index);
	void highlighToIndex(int index);
	void deHighlight(int index);
	bool isStepDone(std::vector<ListNode*>step);

	std::deque<std::vector<ListNode*>> animationQueue;

public:
	SLL();

	~SLL();
	//========================Operation==================
	// Insert After an Index, insert at Head is index -1
	void	insert(int val,int index) ;

	void	remove(int val)  ;

	void	search(int val)  ;
	//======================Animation Control=======================
	void	addStep(std::vector<ListNode*>step);

	void	update() ;

	void	render();

};
