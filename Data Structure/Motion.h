#pragma once
#include "raylib.h"
void slowMovingBetWeen2Pos(Vector2& currPos, Vector2 finalPos);
float Vector2Distance(Vector2 position, Vector2 targetPosition);
//Vector calulation
Vector2 NormalVector(Vector2 position);
Vector2 SubtractVector(Vector2 position, Vector2 targetPosition);
Vector2 Vector2Add(Vector2 position, Vector2 targetPosition);
Vector2 Vector2Scale(Vector2 position, float scale);
//Time Related to smooth animation
float convertTimeToProgress(float time);
float smoothStep(float initValue, float endValue, float time);