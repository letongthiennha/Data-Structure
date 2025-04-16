#include "TextBox.h"

#include "Setting.h"
TextBox::TextBox() {
	m_box.x = 0;
	m_box.y = 0;
	m_box.width = 200;
	m_box.height = 100;
	m_boxColor = textBoxColor;
	m_textColor = BLACK;
	m_maxLength = 0;
	m_isTyping = false;
	m_showBlinker = false;
	m_timer = 0;
	m_isHovering = false;
}
TextBox::TextBox(Vector2 position, Vector2 size, Color boxColor, Color textColor, int maxLength) {
    m_box.x = position.x;
    m_box.y = position.y;
    m_box.width = size.x;
    m_box.height = size.y;
    m_boxColor = boxColor;
    m_textColor = textColor;
    m_maxLength = maxLength;
    m_isTyping = false;
    m_showBlinker = false;
    m_timer = 0;
    m_isHovering = false;

}

//=============Set and Get Text=======================
void TextBox::setText(std::string content) {
    m_content = content;
}

std::string TextBox::getText() { return m_content; }

void TextBox::setBoxTitle(std::string title) { m_textBoxTitle = title; };

//Position and size
void TextBox::setPosition(Vector2 position) {
    m_box.x = position.x;
    m_box.y = position.y;
}
void TextBox::setBoxSize(Vector2 size) {
    m_box.width = size.x;
    m_box.height = size.y;
};

//Clear text
void TextBox::clearContent() { m_content.clear(); }

//Update
void TextBox::update() {
    //Timer
    m_timer += GetFrameTime();
    if (m_timer > 0.75f) {
        m_timer = 0;
        m_showBlinker = !m_showBlinker;
    }
    //Check Hoverigng
    if (CheckCollisionPointRec(GetMousePosition(), m_box)) m_isHovering = true;
    else m_isHovering = false;




    //If hovering and press then enter typing mode
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && m_isHovering) {
        m_isTyping = true;
    }//if not hover and clicked left mouse then exit typing mode
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_isHovering)
        m_isTyping = false;

    if (!m_isTyping) {
        m_boxColor = textBoxColor;
    }
    else m_boxColor = textBoxColorInputing;
    //Enter typing mode
    if (m_isTyping) {
        if (m_content.length() <= m_maxLength) {
            int input = GetCharPressed();
            while (input > 0) {//Check if there is input
                //Only allow alphabet and digit
                if (isalpha(input) || isdigit(input)||input==' ')
                    m_content += (char)(input);
                //Multiple input in 1 second
                input = GetCharPressed();
            }
        }
        //Delete
        if (!m_content.empty() &&(IsKeyPressed(KEY_BACKSPACE))) {
            m_content.pop_back();
        }
    }
}

//Render
void TextBox::renderList() {
    //Draw the box
    DrawRectangleRec(m_box,m_boxColor);
    //Draw OutLine
    DrawRectangleLinesEx(m_box, 2, BLACK);
    //Draw Text
    DrawText(m_content.c_str(), m_box.x + 7, m_box.y + m_box.height *0.5f, textBoxTextSize, m_textColor);
    DrawText(m_textBoxTitle.c_str(), m_box.x, m_box.y- textBoxTitleTextSize, textBoxTitleTextSize, m_textColor);
    //Draw blinker
    if (m_isTyping && m_showBlinker) {
        DrawText("|", m_box.x + 7 + MeasureText(m_content.c_str(), textBoxTextSize), m_box.y + m_box.height*0.5f, textBoxTextSize, m_textColor);
    }
}

