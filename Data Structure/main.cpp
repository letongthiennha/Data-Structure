
#include "raylib.h"
#include "Button.h"
#include "SLL.h"
#include "GUIText.h"
#include "ListNode.h"
int main(void){
    SetTargetFPS(60);
    Font myFont = LoadFont("../include/arial.ttf");

	GUIText text;
	text.setFont(myFont);
	text.setContent("Linked List");
	text.setPosition({ 100,100 });
	text.setTextColor(BLACK);
	text.setTextSize(30);
	text.setSpacing(2);
	text.setMainColor(BLACK);

	text.setAnimationDuration(2);
	text.moveToPosition({ 100, 200 });

	text.addStep();
	text.setAnimationDuration(2);
	text.moveToPosition({ 100, 300 });
	text.addStep();

    InitWindow(1280, 720, "test");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
		text.update();
        text.render();
        EndDrawing();
    }
    
    return 0;
}