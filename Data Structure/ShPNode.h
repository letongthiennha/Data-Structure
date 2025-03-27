#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <cstdio>

class ShPNode {
public:
	ShPNode(Vector2 pos, int id);
	~ShPNode();
	void highlight(bool isActive);
	void setDis(int dis);
	void setPrev(ShPNode* prev);
	int getDis();
	int getId();
	ShPNode* getPrev();
	Vector2 getPos();
	void draw();
	bool visited;
	Vector2 m_pos;
private:
	int m_id;
	int m_dis;
	ShPNode* m_prev;
	bool m_highlight;

	static constexpr float radius = 20.0f;
	static constexpr Color defaultColor = YELLOW;
	static constexpr Color highlightColor = RED;
};