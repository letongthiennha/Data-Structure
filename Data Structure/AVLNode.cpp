#include "AVLNode.h"
#include "Setting.h"

AVLNode::AVLNode(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
    height = 1;
    position = { 0, 0 };
    destination = { 0, 0 };
    isHighlighted = false;
    opacity = 1.0f;
    animationPhase = 0.0f;
    currentAnimation = AVL_IDLE;
}

AVLNode::~AVLNode() {
}

void AVLNode::render(Vector2 pos) {
    Color nodeColor = isHighlighted ? ListNodeHighlightColor : ListNodeColor;
    nodeColor.a = (unsigned char)(opacity * 255);
    DrawCircleV(pos, ListNodeSize / 2, nodeColor);
    DrawCircleLines(pos.x, pos.y, ListNodeSize / 2, BLACK);

    std::string text = std::to_string(value);
    Color textColor = ListNodeTextColor;
    textColor.a = (unsigned char)(opacity * 255);
    DrawText(text.c_str(), pos.x - MeasureText(text.c_str(), 20) / 2, pos.y - 10, 20, textColor);

    // Hiển thị height
    std::string heightText = "h:" + std::to_string(height);
    DrawText(heightText.c_str(), pos.x - MeasureText(heightText.c_str(), 10) / 2, pos.y + 15, 10, textColor);
}
void AVLNode::updateAnimation(float speed) {
    if (currentAnimation == AVL_IDLE) return;
    animationPhase += GetFrameTime() * speed; 
    if (animationPhase >= 1.0f) { 
        animationPhase = 1.0f;
        if (currentAnimation == AVL_CHANGINGOPACITY) {
            opacity = 1.0f; 
        }
        else if (currentAnimation == AVL_MOVING) {
            position = destination; 
        }
        currentAnimation = AVL_IDLE;
    }
    else {
        float t = animationPhase;
        switch (currentAnimation) {
        case AVL_MOVING:
            position.x = position.x * (1 - t) + destination.x * t;
            position.y = position.y * (1 - t) + destination.y * t;
            break;
        case AVL_CHANGINGOPACITY:
            opacity = opacity + (1.0f - opacity) * t;
            break;
        case AVL_HIGHLIGHT:
            isHighlighted = true;
            break;
        default:
            break;
        }
    }
}