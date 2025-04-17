#include "SLLNode.h"
#include "Setting.h"
SLLNode::SLLNode(int val) {
	m_val = val;
	m_currentPosition = { 0, 0 };
	m_destination = { 0, 0 };
	m_isHighlight = false;
	m_opacity = 1.0f;
	m_animationPhase = 0.0f;
	m_currentAnimation = IDLE;
}
SLLNode::~SLLNode() {
}
void SLLNode::renderSLLNode(Vector2 position) {
    Color nodeColor;
    if (this->m_isHighlight) {
        nodeColor = ListNodeHighlightColor;
    }
    else {
        nodeColor = ListNodeColor;
    }
    nodeColor.a = (unsigned char)(this->m_opacity * 255);

    DrawCircleV(position, ListNodeSize / 2, nodeColor);
    DrawCircleLines(position.x, position.y, ListNodeSize / 2, { 0, 0, 0, 255 });

    std::string content = std::to_string(this->m_val);
    Color textColor = ListNodeTextColor;
    textColor.a = (unsigned char)(this->m_opacity * 255);

    DrawText(content.c_str(), position.x - MeasureText(content.c_str(), 20) / 2, position.y - 10, 20, textColor);
};