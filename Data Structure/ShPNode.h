
#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <cstdio>


//class ShPPointer; // Forward declaration since ShPPointer is used below
//
//class ShPNode {
//public:
//    ShPNode(Vector2 pos, int id);
//    ~ShPNode();
//    void highlight(bool isActive);
//    void setDis(int dis);
//    void setPrev(ShPNode* prev);
//    int getDis();
//    int getId();
//    ShPNode* getPrev() const;
//    Vector2 getPos() const;
//    void draw();
//    bool visited;
//    Vector2 m_pos;
//
//    // New methods for adjacency list
//    void addOutgoingEdge(ShPPointer* edge);
//    const std::vector<ShPPointer*>& getOutgoingEdges() const;
//
//private:
//    int m_id;
//    int m_dis;
//    ShPNode* m_prev;
//    bool m_highlight;
//    std::vector<ShPPointer*> m_outgoingEdges; // New vector for outgoing edges
//
//    static constexpr float radius = 20.0f;
//    static constexpr Color defaultColor = YELLOW;
//    static constexpr Color highlightColor = RED;
//};
class ShPPointer;
class ShPNode {
public:
    ShPNode(Vector2 pos, int id);
    ~ShPNode();
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
    void addOutgoingEdge(ShPPointer* edge); // Existing
    void addIncomingEdge(ShPPointer* edge); // New
    const std::vector<ShPPointer*>& getOutgoingEdges() const; // Existing
    const std::vector<ShPPointer*>& getIncomingEdges() const; // New
private:
    int m_id;
    int m_dis;
    ShPNode* m_prev;
    bool m_highlight;
    std::vector<ShPPointer*> m_outgoingEdges; // Existing
    std::vector<ShPPointer*> m_incomingEdges; // New
    static constexpr float radius = 20.0f;
    static constexpr Color defaultColor = YELLOW;
    static constexpr Color highlightColor = RED;
};