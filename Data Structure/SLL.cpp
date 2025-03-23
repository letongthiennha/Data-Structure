#include "SLL.h"
//Constructor and destructor
SLL::SLL() {
	startPostion={ 100,100 };
	distanceBetweenNode = 80;
	m_list = std::vector<ListNode*> (0);
	m_mainBackgroundColor = WHITE;
	m_textColor = GRAY;
	m_highlightBackgroundColor = ORANGE;
	m_highLightTextColor = YELLOW	;
	m_animationDuration = 0.75;
}
SLL::~SLL() {
	for (int i = 0; i < m_list.size(); ++i) {
		delete m_list[i];
		m_list[i] = nullptr;
	}
}
//Calculate Position
Vector2 SLL::positionAtIndex(int index) {
	return Vector2{ startPostion.x + index * distanceBetweenNode,startPostion.y };
}
//==========================Animation Helper=================
void::SLL::moveRightAllAfter(int index) {
	if (index < m_list.size()) {
		std::vector <ListNode*> step;
		for (int i = index; i < m_list.size(); ++i) {
			m_list[i]->moveToPosition(positionAtIndex(i + 1));
			m_list[i]->setAnimationDuration(m_animationDuration);
			m_list[i]->addStep();
			step.push_back(m_list[i]);
		}
		addStep(step);
	}
}
void::SLL::deHighlight(int index) {
	std::vector<ListNode*> highLightStep;
	for (int i = 0; i < index; ++i) {
		m_list[i]->changeBackgroundColor(m_mainBackgroundColor);
		m_list[i]->setAnimationDuration(m_animationDuration);
		m_list[i]->changeTextColor(m_textColor);
		m_list[i]->addStep();
		highLightStep.push_back(m_list[i]);

	}
	addStep(highLightStep);
}
void::SLL::highlighToIndex(int index) {
	for (int i = 0; i < index; ++i) {
		std::vector<ListNode*> highLightStep;
		m_list[i]->changeBackgroundColor(m_highlightBackgroundColor);
		m_list[i]->changeTextColor(m_highLightTextColor);
		m_list[i]->setAnimationDuration(m_animationDuration);

		m_list[i]->addStep();
		highLightStep.push_back(m_list[i]);
		addStep(highLightStep);
	}
}


//========================================Operation==================================
void::SLL::insert(int val,int index) {
	if (index > m_list.size() || index < 0) return;
	highlighToIndex(index);
	moveRightAllAfter(index);
	ListNode* newNode = new ListNode;
	newNode->setVal(val);
	m_list.insert(m_list.begin() + index, newNode);
	if (index + 1 < m_list.size()) {
		newNode->setNext(m_list[index + 1]);
	}

	//Set up the position	
	std::vector <ListNode*>step1;
	newNode->setPosition({ positionAtIndex(index).x ,positionAtIndex(index).y + 100.0f });
	newNode->setMainColor(m_mainBackgroundColor);
	newNode->setTextColor(m_textColor);
	newNode->addStep();
	step1.push_back(newNode);
	addStep(step1);
	//Move in
	std::vector<ListNode*>step2;
	newNode->moveToPosition(positionAtIndex(index));
	newNode->setAnimationDuration(m_animationDuration);
	newNode->addStep();
	step2.push_back(newNode);
	addStep(step2);
	//Back to normal
	deHighlight(index);
}
void::SLL::addStep(std::vector<ListNode*> step) {
	animationQueue.push_back(step);
}
bool::SLL::isStepDone(std::vector<ListNode*>step) {
	for (auto x : step) {
		if (!x->isAnimationDone()) return false;
	}
	return true;
}
void::SLL::update() {
	if (animationQueue.empty()) return;
	if (!isStepDone(animationQueue.front())) {
		for (auto x : animationQueue.front()) {
			x->update();
		}
	}
	else {
		if (animationQueue.empty()) {
			int a;
		}
		for (auto x : animationQueue.front()) {
			x->update();
		}
		if (animationQueue.empty()) {
			int a;
		}
		animationQueue.pop_front();
	}
}
void::SLL::render() {
	for (auto node : m_list){
		node->render();
	}
}