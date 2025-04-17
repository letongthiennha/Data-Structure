#pragma once
#include "raylib.h"
#include "Setting.h"
#include <string>
#include <math.h>

class Pointer {
protected:
    //Tail Position
    Vector2 m_tailPos;
    Vector2 head;
    //===============Color=================
    Color m_color;
public:
    Pointer();
    Pointer(Vector2 firstPosition);
    //==========================Set and get============================
    //===================Color==========
    void setColor(Color color);
    //Head and head Destination
    void setHeadPos(Vector2 headPosition);
   
    //Tail and tail destination
    void setTailPos(Vector2 TailPosition);
   
    //==============================get======================
    Vector2 getTailPos();
    Vector2 getHeadPos();


     void render();

};


