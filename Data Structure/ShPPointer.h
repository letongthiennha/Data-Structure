#pragma once
#include "raylib.h"
#include "ShPNode.h"
#include <string>
#include <math.h>

class ShPPointer {
public:
    ShPPointer(ShPNode* startNode, ShPNode* endNode, int weight);
    ~ShPPointer();

    void setColor(Color color);
    void setWeight(int weight);

    int getWeight();
    ShPNode* getStartNode();
    ShPNode* getEndNode();
    Vector2 getTailPos();
    Vector2 getHeadPos();
    Color getColor();
    bool isVisited() const; // New method to check if the edge is visited
    void setVisited(bool visited); // New method to set the visited status

    void update();
    void render();

private:
    ShPNode* m_startNode;
    ShPNode* m_endNode;
    Vector2 m_tailPos;
    Vector2 m_headPos;
    int m_weight;
    Color m_color;
    bool visited; // New member to track if the edge is visited
};