#include "ShPPointer.h"

ShPPointer::ShPPointer(ShPNode* startNode, ShPNode* endNode, float weight)
    : m_startNode(startNode), m_endNode(endNode), m_weight(weight) {
    m_tailPos = startNode->getPos();
    m_headPos = endNode->getPos();
    m_color = BLACK;
}

ShPPointer::~ShPPointer() {
}

void ShPPointer::setColor(Color color) {
    m_color = color;
}

void ShPPointer::setWeight(int weight) {
    m_weight = weight;
}

int ShPPointer::getWeight() {
    return m_weight;
}

ShPNode* ShPPointer::getStartNode() {
    return m_startNode;
}

ShPNode* ShPPointer::getEndNode() {
    return m_endNode;
}

Vector2 ShPPointer::getTailPos() {
    return m_tailPos;
}

Vector2 ShPPointer::getHeadPos() {
    return m_headPos;
}

void ShPPointer::update() {
    m_tailPos = m_startNode->getPos();
    m_headPos = m_endNode->getPos();
}

void ShPPointer::render() {
    // Vẽ đường 
    DrawLineEx(m_tailPos, m_headPos, 3, m_color);

    // Tính trung điểm đoạn thẳng 
    Vector2 midPoint = { (m_tailPos.x + m_headPos.x) / 2, (m_tailPos.y + m_headPos.y) / 2 };

    // Tìm vecto pháp tuyến 
    Vector2 direction = { m_headPos.x - m_tailPos.x, m_headPos.y - m_tailPos.y };
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0) return;

    Vector2 normalizedDir = { direction.x / length, direction.y / length };
    Vector2 perpendicular = { -normalizedDir.y, normalizedDir.x };

	// Nâng chữ lên xíu để không bị chồng lên đường
    float offsetDistance = 15.0f;
    Vector2 textPos = {
        midPoint.x + perpendicular.x * offsetDistance,
        midPoint.y + perpendicular.y * offsetDistance
    };

    // Vẽ trọng số 
    std::string weightText = std::to_string(static_cast<int>(m_weight));
    DrawText(weightText.c_str(), textPos.x - 4, textPos.y - 8, 20, BLACK);
}