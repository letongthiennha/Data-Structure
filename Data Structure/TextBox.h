#pragma once


#include "Setting.h"

#include <string>

class TextBox {
private:
    //====================Input Text==================
    std::string m_content;
    Color m_textColor;
    //=====Text Length=========
    int m_maxLength;

    //=====================Title=============
    std::string m_textBoxTitle;

    //==========================Box====================
    Rectangle m_box;
    Color m_boxColor;

    //===================Control======================
    //=============State================
    bool m_isHovering;
    bool m_showBlinker;
    bool m_isTyping;
    //============Time==================
    float m_timer;
public:
    //Constructor
    TextBox();
    TextBox(Vector2 position,Vector2 size, Color boxColor, Color textColor,int maxLength);
	void setMaxLength(int maxLength) { m_maxLength = maxLength; };
    //=============Set and Get Text=======================
    void setText(std::string content);
    std::string getText();
	bool isEmpty() { return m_content.empty(); };
    //=============================Set Title===============
    void setBoxTitle(std::string title);

    //Position and size
    void setPosition(Vector2 position);
    void setBoxSize(Vector2 size);

    //Clear text
    void clearContent();

    void update();
    void render();
};
