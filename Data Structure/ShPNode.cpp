#include "ShPNode.h"
ShPNode::ShPNode(Vector2 pos, int id)
    : m_pos(pos), m_id(id), m_dis(INFINITY), m_prev(nullptr), m_highlight(false) {
}
ShPNode::~ShPNode() {
}
void ShPNode::draw() {
    // Draw the node as a circle
    Color nodeColor = m_highlight ? highlightColor : defaultColor;
    DrawCircleV(m_pos, radius, nodeColor);
    DrawCircleLines(m_pos.x, m_pos.y, radius, BLACK);

    // Draw the node ID
    std::string idStr = std::to_string(m_id);
    DrawText(idStr.c_str(), m_pos.x - 4, m_pos.y - 8, 25, BLACK);

    // Draw the distance (total weight) above the node
    char distText[20];
    if (m_dis == std::numeric_limits<int>::max()) {
        sprintf_s(distText, "INF");
    }
    else {
        sprintf_s(distText, "%d", m_dis); 
    }
    DrawText(distText, m_pos.x - 10, m_pos.y - 45, 25, BLACK); // Positioned above the node
}

void ShPNode::highlight(bool isActive) {
    m_highlight = isActive;
}

void ShPNode::setDis(int dis) {
    m_dis = dis;
}

void ShPNode::setPrev(ShPNode* prev) {
    m_prev = prev;
}

int ShPNode::getDis() {
    return m_dis;
}

ShPNode* ShPNode::getPrev() {
    return m_prev;
}

Vector2 ShPNode::getPos() {
    return m_pos;
}

int ShPNode::getId() {
    return m_id;
}