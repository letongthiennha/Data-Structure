#pragma once
#include "raylib.h"
enum nodeAnimation {
	IDLE = 0,
	HIGHLIGHT = 1,
	MOVING = 2,
	CHANGINGOPACITY = 3,
	ADJUSTING = 4
};
class SLLNode {

public:
    //====================Logic====================
    int m_val;
    SLLNode* m_pNext;

	//====================Visual===================
    Vector2 m_currentPosition;
    Vector2 m_destination;

	//====================State Control================
    bool m_isHighlight;
    float m_opacity;
	//======================Animation=================
    float m_animationPhase;
    nodeAnimation m_currentAnimation;

public:

	//====================Constructor=================
	void renderSLLNode(Vector2 position);

	SLLNode(int val);
	~SLLNode();
};