#include "raylib.h"
#include "Button.h"
#include "SLL.h"

int main(void){
 InitWindow(1600, 900, "Data Visualization");
 SetTargetFPS(60);
 LinkedList test;
 Button add(700, 500, 300, 200, "ADD NODE");
 int i = 0;
 enum class state{
        MainMenu,
        choosemenu,
        linkedlist
};
 Button remove(200, 500, 300, 200,"Remove");
state curr=state::MainMenu;
Button Start(800, 450, 300, 200, "Start");
Button array(800, 600, 300, 200, "Array");
Button linkedlist(800, 200, 300, 200, "Linked List");
while (!WindowShouldClose()) {
    switch (curr) {
    case state::MainMenu: {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Start.update();
        Start.render();
        if (Start.isClicked()) {
            curr = state::choosemenu;
        }
        EndDrawing();
        break;
    }
    case state::choosemenu: {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        linkedlist.update();
        array.update();
        array.render();
        linkedlist.render();

        if (linkedlist.isClicked()) {
            curr = state::linkedlist;
        }
        EndDrawing();
        break;
    }
    case state::linkedlist: {
        BeginDrawing();        
        ClearBackground(RAYWHITE);
        remove.update();
        add.update();
        test.update();
        if (add.isClicked()) test.push_back(i++);
        if (remove.isClicked()) test.remove(4);
        add.render();
        remove.render();
        test.render();
        EndDrawing();
    }
    }
}
    CloseWindow();

    return 0;
}