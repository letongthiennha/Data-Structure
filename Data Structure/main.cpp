#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
#include "SLL.h"
#include "Motion.h"
#include "SLLScreen.h"
#include "Slider.h"

int main() {    
    InitWindow(1600, 900, "CS163 DATA STRUCTURE VISUALIZATION");
    SetTargetFPS(60);
		SLLScreen screen;
		Slider slider;
		slider.setPosition({ 1600 - 500, 900 - 500 });
		slider.setSize({ 20, 200 });
    while (!WindowShouldClose()) {
        screen.update();
		BeginDrawing();
		ClearBackground(RAYWHITE);

		screen.render();
		EndDrawing();

  
    }

    CloseWindow();
    return 0;
}