

#include "ShPNode.h"
#include "ShPPointer.h"

ShPNode::ShPNode(Vector2 pos, int id)
    : m_pos(pos), m_id(id), m_dis(INFINITY), m_prev(nullptr), m_highlight(false), visited(false) {
}

ShPNode::~ShPNode() {
}

void ShPNode::draw() {
    Color nodeColor = m_highlight ? highlightColor : defaultColor;
    DrawCircleV(m_pos, radius, nodeColor);
    DrawCircleLines(m_pos.x, m_pos.y, radius, BLACK);

    std::string idStr = std::to_string(m_id);
    DrawText(idStr.c_str(), m_pos.x - 4, m_pos.y - 8, 25, BLACK);

    char distText[20];
    if (m_dis == std::numeric_limits<int>::max()) {
        sprintf_s(distText, "INF");
    }
    else {
        sprintf_s(distText, "%d", m_dis);
    }
    DrawText(distText, m_pos.x - 20, m_pos.y - 55, 30, RED);
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

ShPNode* ShPNode::getPrev() const {
    return m_prev;
}

Vector2 ShPNode::getPos() const {
    return m_pos;
}

int ShPNode::getId() {
    return m_id;
}

void ShPNode::addOutgoingEdge(ShPPointer* edge) {
    m_outgoingEdges.push_back(edge);
}

void ShPNode::addIncomingEdge(ShPPointer* edge) {
    m_incomingEdges.push_back(edge);
}

const std::vector<ShPPointer*>& ShPNode::getOutgoingEdges() const {
    return m_outgoingEdges;
}

const std::vector<ShPPointer*>& ShPNode::getIncomingEdges() const {
    return m_incomingEdges;
}