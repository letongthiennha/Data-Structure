#pragma once

#include <climits>
#include <string>
#include "raylib.h"
#include "Motion.h"
#include "Setting.h"

const int EMPTY = INT_MIN;

class HashTableCell {
public:
    int val;

    HashTableCell(int val);
    ~HashTableCell();
    void setValue(int value);
    void setPosition(Vector2 pos);
    void setTargetPosition(Vector2 targetpos);
    //void setHighlight(float duration);
    //void setPersistentHighlight();
    //void unHighlight();

    void update(float deltaTime);
    void render();

private:
    Vector2 position;
    Vector2 targetPosition;
    Color backgroundColor;
    Color textColor;
    //float highlightTimer;
    //bool isHighlighted;
    //bool isPersistentHighlighted;
};