#pragma once
#include "raylib.h"
#include<string>
class Button  {
private:
    Rectangle hitBox;
    bool isActive = true;
    //State
    bool isSelected = false;
    Vector2 m_size;
    Vector2 m_position;

    //Color
    Color m_idleColor=BLACK;
    Color m_hoverColor=YELLOW;
    Color m_activeColor=RED;
    Color m_color;
    //Text
    int m_textSize=30;
    std::string m_text="";

    //Texture
    Texture2D m_texture;
public:


    // Constructor
    Button() = default;
    Button(Vector2 position,Vector2 size, std::string text);


    // Destructor
     ~Button() = default;
//====================================Color===========================
    //Set Color
    void SetIdleColor(Color color);
    void SetHoverColor(Color color);
    void SetActiveColor(Color color);
    void SetColor(Color idle, Color hovering, Color clicked);
    void setTexture(std::string path);

    //====================================Text=====================
    //Set Text
    void setText(std::string, int textSize);
    void SetTextSize(int textSize);
    //Get Text
    int getTextSize();

    //================================Position And Size=====================
    void setPosition(Vector2 position);
    Vector2 getPosition();
    void setSize(Vector2 size);

    //=================================State===================
    bool isHover() const;
    bool isClicked() const;
    void Select();
    void unSelect();
    void active();
    void deactive();

    //============================= Update======================
    void update();
    //=============================DrawShape=========================
    void renderRectangle();
    void drawRoundedRectangle(int roundness);
    void drawOutline(int roundness, int segments, int thickness, Color color);

    void drawTexture();
    void drawText(Color color);
};
