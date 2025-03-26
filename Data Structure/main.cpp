    
#include "raylib.h"
#include "Pointer.h"
#include "TextBox.h"
int main(void){
    Pointer a({ 100,100 });
    a.setTargetHeadPos({ 200,400 });
    a.setTargetTailPos({ 50,600 });
    SetTargetFPS(60);
    InitWindow(1600, 900, "test");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        a.update();
        a.render();
        EndDrawing();
    }
    
    return 0;
}