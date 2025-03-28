#pragma once

#include <climits>
#include <string>
#include "raylib.h"
#include "Motion.h"


const int EMPTY = INT_MIN;

class HashTableCell {
public:
    int val;
    int index;

    HashTableCell(int val);
    ~HashTableCell();

    Vector2 getPosition();
    Vector2 getTargetPosition();

    void setValue(int value);
    void setinitPosition (Vector2 pos);
    void setPosition(Vector2 pos);
    void setTargetPosition(Vector2 targetpos);
    void setHighlight(float duration);
    void setPersistentHighlight();
    void unHighlight();
    void update(float deltaTime);
    void render();

private:
    Vector2 position;
    Vector2 targetPosition;
    Color backgroundColor;
    Color textColor;
    float highlightTimer;
    bool isHighlighted;
    bool isPersistentHighlighted;
};