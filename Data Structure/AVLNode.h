#pragma once
#include "raylib.h"

enum AVLAnimation {
    AVL_IDLE = 0,
    AVL_HIGHLIGHT = 1,
    AVL_MOVING = 2,
    AVL_CHANGINGOPACITY = 3
};

class AVLNode {
public:
    int value;               
    AVLNode* left;          
    AVLNode* right;           
    int height;               
    Vector2 position;     
    Vector2 destination;      
    bool isHighlighted;       
    float opacity;            
    float animationPhase;     
    AVLAnimation currentAnimation; 

    AVLNode(int val);
    ~AVLNode();
    void render(Vector2 pos);
    void updateAnimation(float speed);
};
