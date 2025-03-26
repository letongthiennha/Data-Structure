#pragma once
#include "raylib.h"
#include "Setting.h"
#include <string>
#include <math.h>

class Arrow {
public:
    Arrow(Vector2 pos);

    void setDestination(Vector2 destination);
    void setTargetDestination(Vector2 targetDes);
    void setPosition(Vector2 position);
    void setTargetPosition(Vector2 targetPos);
    Vector2 getPosition();
    Vector2 getDestination();
    void setColor(Color color);

    virtual void renderArrow(Vector2 position, Vector2 destination);
    virtual void update();
    virtual void render();
protected:
    Vector2 position;
    Vector2 destination;
    Vector2 targetDestination;
    Vector2 targetPosition;
    Color color = BLACK;
};


