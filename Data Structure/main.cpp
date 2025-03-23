
#include "raylib.h"
#include "Button.h"
#include "SLL.h"
#include "GUIText.h"
#include "ListNode.h"
#include "SLL.h"
int main(void){
	SLL myList;
	myList.insert(1,0);
    myList.insert(2, 0);
    myList.insert(5, 1);
    myList.insert(6, 2);
    SetTargetFPS(60);
    InitWindow(1280, 720, "test");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
		myList.update();
		myList.render();
        EndDrawing();
    }
    
    return 0;
}