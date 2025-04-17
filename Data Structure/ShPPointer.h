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

    int getWeight() const;
    ShPNode* getStartNode() const;
    ShPNode* getEndNode() const;
    Vector2 getTailPos() const;
    Vector2 getHeadPos() const;
    Color getColor() const;
    bool isVisited() const; 
    void setVisited(bool visited); 
    void update();
    void render();

private:
    ShPNode* m_startNode;
    ShPNode* m_endNode;
    Vector2 m_tailPos;
    Vector2 m_headPos;
    int m_weight;
    Color m_color;
    bool visited;
};