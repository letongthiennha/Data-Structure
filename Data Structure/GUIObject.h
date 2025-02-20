#pragma once
#include "raylib.h"
class GUIObject {
public:
	Vector2 pos{ 0.0f,0.0f };
	GUIObject(float x, float y);
	GUIObject() = default;

	virtual void render() = 0;

	~GUIObject() = default;
};
