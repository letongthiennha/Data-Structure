
#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <cstdio>



class ShPPointer;
class ShPNode {
public:
    ShPNode(Vector2 pos, int id);
    ~ShPNode();
    void setPos(Vector2 pos);
    static float getRadius();
    void highlight(bool isActive);
    void setDis(int dis);
    void setPrev(ShPNode* prev);
    int getDis();
    int getId();
    ShPNode* getPrev() const;
    Vector2 getPos() const;
    void draw();
    bool visited;
    Vector2 m_pos;
    void addOutgoingEdge(ShPPointer* edge);
    void addIncomingEdge(ShPPointer* edge); 
    const std::vector<ShPPointer*>& getOutgoingEdges() const; 
    const std::vector<ShPPointer*>& getIncomingEdges() const; 
private:
    int m_id;
    int m_dis;
    ShPNode* m_prev;
    bool m_highlight;
    bool m_curr;
    std::vector<ShPPointer*> m_outgoingEdges; 
    std::vector<ShPPointer*> m_incomingEdges; 
    static constexpr float radius = 15.0f;
};