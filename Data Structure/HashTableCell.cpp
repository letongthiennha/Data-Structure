#include "HashTableCell.h"
#include <random>

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
    if (isHighlighted || isPersistentHighlighted) {
        backgroundColor = ORANGE;
        textColor = GOLD;
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
            int textWidth = MeasureText(std::to_string(val).c_str(), 20);
            int textX = position.x + (50 - textWidth) / 2; // Center the text horizontally
            int textY = position.y ; 
            DrawText(std::to_string(val).c_str(), textX, textY + 15, 20, textColor);
        }
        DrawText(std::to_string(index).c_str(), position.x + 20, position.y + 60, 15, textColor);
}
