
#include "raylib.h"
#include "Button.h"
#include "SLL.h"
#include "GUIText.h"

int main(void){
    SetTargetFPS(60);
    Font myFont = LoadFont(".. / include / arial.ttf");
    GUIText myText;
    myText.setMovingDuration(2);
    myText.setContent("Hello World");
    myText.setFont(myFont);
    myText.moveToPosition({ 400, 300 });
    myText.addStep();
    myText.setColoringDuration(2);
    myText.changeColor(RED);
    myText.addStep();
    myText.moveToPosition({ 0, 0 });
    myText.addStep();
    myText.changeColor(BLUE);
	myText.addStep();
    InitWindow(1280, 720, "test");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        myText.update();
        myText.render();
        EndDrawing();
    }
    
    return 0;
}