#include "Motion.h"
#include "Setting.h"
#include "math.h"
#include <cmath>
void slowMovingBetWeen2Pos(Vector2& currPos, Vector2 finalPos) {
    if (currPos.x == finalPos.x && currPos.y == finalPos.y) return;
    float deltaTime = GetFrameTime();
    if (currPos.x != finalPos.x || currPos.y != finalPos.y) {
        float xDistance = finalPos.x - currPos.x;
        float yDistance = finalPos.y - currPos.y;
        float totalDistance = sqrt(xDistance * xDistance + yDistance * yDistance);

        float dx = xDistance / totalDistance * speed* deltaTime;
        float dy = yDistance / totalDistance * speed* deltaTime;

        if (sqrt(dx * dx + dy * dy) >=totalDistance) {
            currPos = finalPos; return;
        }

        Vector2 newPos{ currPos.x + dx,currPos.y + dy };
        // If move pass then snap back
        if ((xDistance >= 0 && newPos.x >= finalPos.x) || (xDistance <= 0 && newPos.x <= finalPos.x))
            newPos.x = finalPos.x;
        if ((yDistance >= 0 && newPos.y >= finalPos.y) || (yDistance <= 0 && newPos.y <= finalPos.y))
            newPos.y = finalPos.y;

        currPos.x = newPos.x;
        currPos.y = newPos.y;
    }
}
float Vector2Distance(Vector2 position,Vector2 targetPosition) {
	return sqrt(pow(position.x - targetPosition.x, 2) + pow(position.y - targetPosition.y, 2));
}
Vector2 NormalVector(Vector2 position) {
	float distance = sqrt(pow(position.x, 2) + pow(position.y, 2));
	if (distance== 0) return { 0,0 };
	float normalX = position.x / distance;
	float normalY = position.y / distance;
	return {normalX,normalY};
}
Vector2 SubtractVector(Vector2 position, Vector2 targetPosition) {
	return {position.x - targetPosition.x,position.y - targetPosition.y };
}
Vector2 Vector2Add(Vector2 position, Vector2 targetPosition) {
	return { position.x + targetPosition.x,position.y + targetPosition.y };
}
Vector2 Vector2Scale(Vector2 position, float scale) {
	return { position.x * scale,position.y * scale };
}

float convertTimeToProgress(float time) {
    if (time < 0.0f) time = 0.0f;
    if (time > 1.0f) time = 1.0f;


    return 0.5f * (1.0f - cosf(time * 3.14159265f));
}

float smoothStep(float start, float end, float t) {

	return start + (end - start) * t;
}
