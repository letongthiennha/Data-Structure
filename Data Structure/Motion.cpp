#include "Motion.h"
#include "Setting.h"
#include "math.h"
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