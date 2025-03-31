#include "ShPTextBox.h"
#include <cctype>
#include <sstream>
#include <vector>

// Static constant definitions
const Color ShPTextBox::textBoxColor = WHITE;
const Color ShPTextBox::textBoxColorInputing = LIGHTGRAY;
const int ShPTextBox::textBoxTextSize = 20;

ShPTextBox::ShPTextBox(Vector2 position, Vector2 size, Color boxColor, Color textColor, int maxLength) {
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

void ShPTextBox::update() {
    // Update blinker timer
    m_timer += GetFrameTime();
    if (m_timer > 0.75f) {
        m_timer = 0;
        m_showBlinker = !m_showBlinker;
    }

    // Check if mouse is hovering
    m_isHovering = CheckCollisionPointRec(GetMousePosition(), m_box);

    // Enter/exit typing mode
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && m_isHovering) {
        m_isTyping = true;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_isHovering) {
        m_isTyping = false;
    }

    // Set color based on typing state
    m_boxColor = m_isTyping ? textBoxColorInputing : textBoxColor;

    // Handle typing
    if (m_isTyping) {
        // Handle character input
        int input = GetCharPressed();
        while (input > 0) {
            if (m_content.length() < m_maxLength) {
                if (isalpha(input) || isdigit(input) || input == ' ' || input == '-') {
                    m_content += (char)input;
                }
            }
            input = GetCharPressed();
        }

        // Handle backspace
        if (!m_content.empty() && IsKeyPressed(KEY_BACKSPACE)) {
            m_content.pop_back();
        }

        // Handle Enter key for new line
        if (IsKeyPressed(KEY_ENTER) && m_content.length() < m_maxLength) {
            m_content += '\n';
        }
    }
}

void ShPTextBox::render() {
    // Draw the textbox
    DrawRectangleRec(m_box, m_boxColor);
    DrawRectangleLinesEx(m_box, 2, BLACK);

    // Split m_content into lines
    std::vector<std::string> lines;
    std::stringstream ss(m_content);
    std::string line;
    while (std::getline(ss, line, '\n')) {
        lines.push_back(line);
    }

    // Draw each line
    float y = m_box.y + 5;  // Top padding
    for (size_t i = 0; i < lines.size(); ++i) {
        DrawText(lines[i].c_str(), m_box.x + 7, y + i * textBoxTextSize, textBoxTextSize, m_textColor);
    }

    // Draw blinker if typing
    if (m_isTyping && m_showBlinker) {
        if (lines.empty()) {
            DrawText("|", m_box.x + 7, y, textBoxTextSize, m_textColor);
        }
        else {
            size_t cursorLine = lines.size() - 1;
            if (lines.back().empty()) {
                // Cursor at beginning of the last line
                DrawText("|", m_box.x + 7, y + cursorLine * textBoxTextSize, textBoxTextSize, m_textColor);
            }
            else {
                // Cursor after the last character of the last line
                int textWidth = MeasureText(lines.back().c_str(), textBoxTextSize);
                DrawText("|", m_box.x + 7 + textWidth, y + cursorLine * textBoxTextSize, textBoxTextSize, m_textColor);
            }
        }
    }
}

void ShPTextBox::setText(std::string content) {
    m_content = content;
}

std::string ShPTextBox::getText() {
    return m_content;
}

void ShPTextBox::clearContent() {
    m_content.clear();
}

void ShPTextBox::setPosition(Vector2 position) {
    m_box.x = position.x;
    m_box.y = position.y;
}

void ShPTextBox::setBoxSize(Vector2 size) {
    m_box.width = size.x;
    m_box.height = size.y;
}