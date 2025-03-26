#include "Pointer.h"

Arrow::Arrow(Vector2 pos) : position(pos), targetPosition(pos), destination(pos), targetDestination(pos) {}

void Arrow::setDestination(Vector2 destination) {
    this->destination = destination;
    this->targetDestination = destination;
}

void Arrow::setTargetDestination(Vector2 targetDes) {
    this->targetDestination = targetDes;
}

void Arrow::setPosition(Vector2 position) {
    this->position = position;
    this->targetPosition = position;
}

void Arrow::setTargetPosition(Vector2 targetPos) {
    this->targetPosition = targetPos;
}

Vector2 Arrow::getPosition() {
    return position;
}

Vector2 Arrow::getDestination() {
    return destination;
}

void Arrow::setColor(Color color) {
    this->color = color;
}

void Arrow::update() {
    if (destination.x == targetDestination.x && destination.y == targetDestination.y && position.x == targetPosition.x && position.y == targetPosition.y) return;

    float deltaTime = GetFrameTime();

    if (destination.x != targetDestination.x || destination.y != targetDestination.y) {
        float distanceX = targetDestination.x - destination.x;
        float distanceY = targetDestination.y - destination.y;
        float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

        float dX = distanceX / distance * speed * deltaTime;
        float dY = distanceY / distance * speed * deltaTime;

        if (fabs(dX) >= fabs(distanceX) && fabs(dY) >= fabs(distanceY)) {
            destination = targetDestination;
        }
        else {
            destination.x += dX;
            destination.y += dY;
        }
    }

    if (position.x != targetPosition.x || position.y != targetPosition.y) {
        float distanceX = targetPosition.x - position.x;
        float distanceY = targetPosition.y - position.y;
        float dis = sqrt(distanceX * distanceX + distanceY * distanceY);

        float dX = distanceX / dis * speed * deltaTime;
        float dY = distanceY / dis * speed * deltaTime;

        if (fabs(dX) >= fabs(distanceX) && fabs(dY) >= fabs(distanceY)) {
            position = targetPosition;
        }
        else {
            position.x += dX;
            position.y += dY;
        }
    }
}

void Arrow::renderArrow(Vector2 position, Vector2 destination) {
    DrawCircle(position.x, position.y, 2, color);
    DrawLineEx(position, destination, 2, color);

    Vector2 direction = { destination.x - position.x,destination.y - position.y };
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0) return;

    direction.x /= length;
    direction.y /= length;

    Vector2 ArrowHead = destination;
    Vector2 left = { ArrowHead.x - direction.x * 10.0f + direction.y * 5.0f, ArrowHead.y - direction.y * 10.0f - direction.x * 5.0f };
    Vector2 right = { ArrowHead.x - direction.x * 10.0f - direction.y * 5.0f, ArrowHead.y - direction.y * 10.0f + direction.x * 5.0f };

    DrawTriangle(ArrowHead, left, right, color);
}

void Arrow::render() {
    renderArrow(position, destination);
}


