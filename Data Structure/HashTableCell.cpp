#include "HashTableCell.h"

HashTableCell::HashTableCell(int val) : val(val), backgroundColor(WHITE), textColor(BLACK), isHighlighted(false), isPersistentHighlighted(false) {}

HashTableCell::~HashTableCell() {
    val = EMPTY;
}

Vector2 HashTableCell::getPosition() {
    return position;
}
Vector2 HashTableCell::getTargetPosition() {
    return targetPosition;
}

void HashTableCell::setValue(int value) {
    val = value;
}

void HashTableCell::setinitPosition(Vector2 pos) {
    position = pos;
}

void HashTableCell::setPosition(Vector2 pos) {
    position = pos;
    targetPosition = pos;
}

void HashTableCell::setTargetPosition(Vector2 targetpos) {
    targetPosition = targetpos;
}

void HashTableCell::setHighlight(float duration) {
    highlightTimer = duration;
    isHighlighted = true;
}
void HashTableCell::unHighlight() {
    isHighlighted = false;
    isPersistentHighlighted = false;
}
void HashTableCell::setPersistentHighlight() {
    isPersistentHighlighted = true;
}

void HashTableCell::update(float deltaTime) {
    if (isHighlighted && !isPersistentHighlighted) {
        highlightTimer -= deltaTime;
        if (highlightTimer <= 0) {
            unHighlight();
        }
    }
    if (isHighlighted) {
        backgroundColor = ORANGE;
        textColor = GOLD;
    } else if (isPersistentHighlighted) {
        backgroundColor = GREEN;
        textColor = BLACK;
    }
    else {
        backgroundColor = WHITE;
        textColor = BLACK;
    }
    if (position.x != targetPosition.x && position.y != targetPosition.y) {
        slowMovingBetWeen2Pos(position, targetPosition);
    }
}

void HashTableCell::render() {
        DrawRectangle(position.x, position.y, 50, 50, backgroundColor);
        DrawRectangleLines(position.x, position.y, 50, 50, BLACK);
        if (val != EMPTY) {
            if (!areFontsLoaded()) {
                float textWidth = MeasureText(std::to_string(val).c_str(), 20);
                float textX = position.x + (50 - textWidth) / 2; 
                float textY = position.y + (50 - 20) / 2; 
                DrawText(std::to_string(val).c_str(), textX, textY, 20, textColor);
            }
            else {
                float textWidth = MeasureTextEx(FuturaMedium, std::to_string(val).c_str(), 22, 1).x;
                float textHeight = MeasureTextEx(FuturaMedium, std::to_string(val).c_str(), 22, 1).y;
                float textX = position.x + (50 - textWidth) / 2; 
                float textY = position.y + (50 - textHeight) / 2; 
                DrawTextEx(FuturaMedium, std::to_string(val).c_str(), {textX, textY}, 22, 1, BLACK);
            }
        }
        if (!areFontsLoaded()) DrawText(std::to_string(index).c_str(), position.x + 20, position.y + 60, 15, textColor);
        else {
            float indexWidth = MeasureTextEx(FuturaMedium, std::to_string(index).c_str(), 17, 1).x;
            float indexHeight = MeasureTextEx(FuturaMedium, std::to_string(index).c_str(), 17, 1).y;
            DrawTextEx(FuturaMedium, std::to_string(index).c_str(), {position.x + (50-indexWidth)/2, position.y+50+indexHeight/2}, 17, 1, BLACK);
        }
}
