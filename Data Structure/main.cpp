#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
#include "Application.h"
int main() {    
	InitWindow(1600, 900, "CS163 DSA Visulization");
	SetTargetFPS(60);
	Application app;
	app.run();
	CloseWindow();
    return 0;
}