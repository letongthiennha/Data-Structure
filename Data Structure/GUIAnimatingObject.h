//#pragma once
//#define defaultFPS 60
//
//#include "raylib.h"
//#include "GUIObject.h"
//#include "queue"
//
//inline bool isSameColor(Color c1, Color c2) {
//	return (c1.r == c2.r) &&
//		(c1.g == c2.g) &&
//		(c1.b == c2.b) &&
//		(c1.a == c2.a);
//}
//inline bool isSamePosition(Vector2 v1, Vector2 v2) {
//	return (v1.x == v2.x) && (v1.y == v2.y);
//}
//inline bool isSameState(std::unique_ptr<GUIState> s1, std::unique_ptr<GUIState> s2) {
//	return isSameColor(s1->getMainColor(), s2->getMainColor()) && isSamePosition(s1->getPosition(), s2->getPosition());
//}
//
////Abstract Class For any Animating Object, Update state step by step after 1 Frame
//class GUIAnimatingObject : public GUIObject {
//protected:
//	struct instruction {
//		std::unique_ptr<GUIState> m_targetState;
//		float time;
//		instruction() : m_targetState(nullptr), time(0.0f) {}
//		instruction(const instruction& other)
//			: /* copy other members */
//			m_targetState(other.m_targetState ? std::make_unique<GUIState>(*other.m_targetState) : nullptr),time(other.time)
//		{
//		}
//
//		instruction& operator=(const instruction& other) {
//			if (this != &other) {
//				// Copy other members...
//				m_targetState = other.m_targetState ? std::make_unique<GUIState>(*other.m_targetState) : nullptr;
//			}
//			return *this;
//		};
//	};
//	//=================State Control=================
//	//Helper Pointer to determine next state
//	std::unique_ptr<GUIState> m_targetState = std::make_unique<GUIState>(*m_state);
//
//	//================Flow Control==============
//
//	//History queue for undo features
//	std::deque<instruction> m_historyQueue;
//
//	//Target Status
//	std::deque<instruction> m_animationQueue;
//
//	//Future for redo features
//	std::deque<instruction> m_futureQueue;
//
//	//=======================Animation Control======================
//	float				m_animationTime = 0;
//	instruction			m_buildingInstruction;
//	//Change Color Status
//	float				m_ChangingColorSpeed;
//
//	Vector3				deltaColor;
//	//Moving Status
//	float				m_MovingSpeed;
//
//
//public:
//	//=================================================Timing Function=======================
//	virtual void		setAnimationDuration(float time);
//	//=================================================Position Function=======================================
//	virtual void		setPosition(Vector2 position) override,
//						//After Use This Function, must confirm Step to do it
//
//						moveToPosition(Vector2 newPos); //Move Slowly
//
//	//=================================================Coloring Function=======================================
//	virtual void		setMainColor(Color color) override,
//						//After Use This Function, must confirm Step to do it
//						changeColor(Color color);
//
//	//=======================Update Function============================
//	//Update after 1 frame
//	virtual void		update_position(),
//						update_color(),
//						update(),
//						//Render frame
//						render()  = 0;
//
//	virtual ~GUIAnimatingObject() = default;
//
//	//=======================Confirm Step============================
//
//	virtual void addStep();	
//	bool isAnimationDone();
//	//=======================Constructor============================
//	GUIAnimatingObject()
//		: deltaColor({ 0,0,0 }), m_ChangingColorSpeed(1.0f),
//		 m_MovingSpeed(1.0f) {
//		m_state = std::make_unique<GUIState>();
//		m_targetState = std::make_unique<GUIState>(*m_state);
//	}
//};
