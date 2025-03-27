#pragma once
#include "raylib.h"
#include "ShPNode.h"
#include <string>
#include <math.h>

class ShPPointer {
protected:
    ShPNode* m_startNode;
    ShPNode* m_endNode;
    Vector2 m_tailPos;
    Vector2 m_headPos;
    int m_weight;
    Color m_color;

public:
    ShPPointer(ShPNode* startNode, ShPNode* endNode, float weight);
    ~ShPPointer();

    void setColor(Color color);
    void setWeight(int weight);

    int getWeight();
    ShPNode* getStartNode();
    ShPNode* getEndNode();
    Vector2 getTailPos();
    Vector2 getHeadPos();

    void update();
    void render();
};