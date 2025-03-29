#include "ShPPointer.h"

ShPPointer::ShPPointer(ShPNode* startNode, ShPNode* endNode, int weight)
    : m_startNode(startNode), m_endNode(endNode), m_weight(weight), m_color(BLACK), visited(false) {
}


ShPPointer::~ShPPointer() {
}

bool ShPPointer::isVisited() const {
    return visited;
}
void ShPPointer::setVisited(bool visited) {
    this->visited = visited;
}
Color ShPPointer::getColor() const {
    return m_color;
}
void ShPPointer::setColor(Color color) {
    m_color = color;
}

void ShPPointer::setWeight(int weight) {
    m_weight = weight;
}

int ShPPointer::getWeight() const {
    return m_weight;
}

ShPNode* ShPPointer::getStartNode() const {
    return m_startNode;
}

ShPNode* ShPPointer::getEndNode() const {
    return m_endNode;
}

Vector2 ShPPointer::getTailPos() const {
    return m_tailPos;
}

Vector2 ShPPointer::getHeadPos() const {
    return m_headPos;
}

void ShPPointer::update() {
    m_tailPos = m_startNode->getPos();
    m_headPos = m_endNode->getPos();
}

void ShPPointer::render() {
    DrawLineEx(m_tailPos, m_headPos, 2.0f, m_color);

    Vector2 midPoint = { (m_tailPos.x + m_headPos.x) / 2, (m_tailPos.y + m_headPos.y) / 2 };

    float angle = atan2(m_headPos.y - m_tailPos.y, m_headPos.x - m_tailPos.x);

    float offsetX = 10.0f * sin(angle);
    float offsetY = -10.0f * cos(angle);

    Vector2 textPos = { midPoint.x + offsetX, midPoint.y + offsetY };
    char weightText[10];
    snprintf(weightText, sizeof(weightText), "%d", m_weight);

    DrawText(weightText, textPos.x, textPos.y, 20, BLACK);
}