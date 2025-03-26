#pragma once
#include "raylib.h"
#include "Setting.h"
#include <string>
#include <math.h>

class Pointer {
protected:
    //Tail Position
    Vector2 m_tailPos;
    Vector2 m_tailTargetPos;
    //Head
    Vector2 m_headPos;
    Vector2 m_headTargetPos;
    //===============Color=================
    Color m_color;
public:
    Pointer(Vector2 firstPosition);
    //==========================Set and get============================
    //===================Color==========
    void setColor(Color color);
    //Head and head Destination
    void setHeadPos(Vector2 headPosition);
    void setTargetHeadPos(Vector2 targetHeadPosition);

    //Tail and tail destination
    void setTailPos(Vector2 TailPosition);
    void setTargetTailPos(Vector2 targetTail);

    //==============================get======================
    Vector2 getTailPos();
    Vector2 getHeadPos();


    virtual void update();
    virtual void render();

};


