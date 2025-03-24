
#include "raylib.h"
#include "Button.h"
#include "SLL.h"
#include "GUIText.h"
#include "ListNode.h"
#include "SLL.h"
#include"Button.h"
int main(void){
    Button test;
    test.setText("Test", 20);
    test.setPosition({ 100,100 });
    test.SetColor(BLUE, RED, YELLOW);
    test.setSize({ 500,100 });
    SetTargetFPS(60);
    InitWindow(1280, 720, "test");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        test.update();
        test.drawRectangle();
        test.drawText(BLACK);
        EndDrawing();
    }
    
    return 0;
}