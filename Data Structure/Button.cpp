#include "Button.h"

Button::Button(Vector2 position, Vector2 size, std::string text) {
    m_position = position;
    m_size = size;
    m_text = text;
    hitBox = { m_position.x, m_position.y, m_size.x, m_size.y };
}
//=====================Color========================
void Button::SetIdleColor(Color color) {
    m_idleColor = color;
}

void Button::SetHoverColor(Color color) {
    m_hoverColor = color;
}

void Button::SetActiveColor(Color color) {
    m_activeColor = color;
}

void Button::SetColor(Color idle, Color Clicked, Color hover) {
    m_idleColor = idle;
    m_activeColor = Clicked;
    m_hoverColor = hover;
}
//===================================Text==========================
void Button::SetTextSize(int textSize) {
    m_textSize = textSize;
}

void Button::setText(std::string text, int textSize) {
    m_text = text;
    m_textSize = textSize;
}

int Button::getTextSize() {
    return m_textSize;
}
//===============================Position and size======================
void Button::setPosition(Vector2 position) {
    m_position = position;
    hitBox.x = position.x;
    hitBox.y = position.y;
}
Vector2 Button::getPosition() {
    return m_position;
}

void Button::setSize(Vector2 size) {
    m_size = size;
    hitBox.width = size.x;
    hitBox.height = size.y;
}
//===============================State=============================

bool Button::isHover()  {
    Vector2 mousePos = GetMousePosition();
    return isActive&&CheckCollisionPointRec(mousePos, hitBox);
}

bool Button::isClicked()  {
    return (isHover() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

void Button::Select() {
    isSelected = true;
}

void Button::unSelect() {
    isSelected = false;
}

void Button::active() {
    isActive = true;
}

void Button::deactive() {
    isActive = false;
}

void Button::update() {
    if (isClicked()) m_color = m_activeColor;
    else
    if (isHover()) m_color = m_hoverColor;
    else m_color = m_idleColor;
}
//=================================Draw===============================

void Button::drawRectangle() {
    DrawRectangle(m_position.x, m_position.y, m_size.x, m_size.y,m_color);
}

void Button::drawRoundedRectangle(int roundness) {

    DrawRectangleRounded(hitBox, roundness / 100.0f, 10, m_color);
}

void Button::drawOutline(int roundness, int segments, int thickness, Color color) {
    DrawRectangleLinesEx(hitBox, thickness, color);
}

void Button::drawTexture(Vector2 texturePosition) {
    if (m_texture.id > 0) {
        DrawTexture(m_texture, texturePosition.x, texturePosition.y, WHITE);
    }
}

void Button::drawText(Color color) {
    DrawText(m_text.c_str(), m_position.x + m_size.x / 2 -MeasureText(m_text.c_str(),m_textSize), m_position.y + m_size.y / 2, m_textSize, color);
}
