#include "HashTableCell.h"

HashTableCell::HashTableCell(int val) : val(val), position({ 0,0 }), backgroundColor(WHITE), textColor(BLACK) /*isHighlighted(false), isPersistentHighlighted(false) */ {}

HashTableCell::~HashTableCell() {
    val = EMPTY;
}

void HashTableCell::setValue(int value) {
    val = value;
}

void HashTableCell::setPosition(Vector2 pos) {
    position = pos;
    targetPosition = pos;
}

void HashTableCell::setTargetPosition(Vector2 targetpos) {
    targetPosition = targetpos;
}
/*
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
 */
void HashTableCell::update(float deltaTime) {
    /* if (isHighlighted && !isPersistentHighlighted) {
        highlightTimer -= deltaTime;
        if (highlightTimer <= 0) {
            unHighlight();
        }
    }
    if (isHighlighted || isPersistentHighlighted) {
        backgroundColor = ORANGE;
        textColor = YELLOW;
    }
    else {
        backgroundColor = WHITE;
        textColor = BLACK;
    } */
    if (position.x != targetPosition.x && position.y != targetPosition.y) {
        slowMovingBetWeen2Pos(position, targetPosition);
    }
}

void HashTableCell::render() {
        DrawRectangle(position.x, position.y, 50, 50, backgroundColor);
        if (val!=EMPTY) DrawText(std::to_string(val).c_str(), position.x + 10, position.y + 10, 20, textColor);
}
