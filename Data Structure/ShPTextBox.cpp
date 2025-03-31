#include "ShPTextBox.h"
#include <cctype>
#include <sstream>
#include <algorithm>

// Static constant definitions
const Color ShPTextBox::textBoxColor = WHITE;
const Color ShPTextBox::textBoxColorInputing = LIGHTGRAY;
const int ShPTextBox::textBoxTextSize = 20;

ShPTextBox::ShPTextBox(Vector2 position, Vector2 size, Color boxColor, Color textColor, int maxLength)
    : m_box{ position.x, position.y, size.x, size.y },
    m_boxColor(boxColor),
    m_textColor(textColor),
    m_maxLength(maxLength),
    m_isTyping(false),
    m_showBlinker(false),
    m_timer(0),
    m_isHovering(false),
    m_cursorPos(0),
    m_firstVisibleLine(0) {
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
        // Calculate cursor position based on mouse click
        float top = m_box.y + 5;
        float relativeY = GetMouseY() - top;
        int relativeLine = static_cast<int>(relativeY / textBoxTextSize);
        if (relativeLine < 0) relativeLine = 0;

        auto lines = splitIntoLines(m_content);
        size_t actualLine = m_firstVisibleLine + relativeLine;
        if (actualLine >= lines.size()) actualLine = lines.size() - 1;
        if (actualLine < 0) actualLine = 0;

        // Calculate pos within the line
        std::string currentLine = (actualLine < lines.size()) ? lines[actualLine] : "";
        float x_base = m_box.x + 7;
        float mouseX = GetMouseX();
        size_t pos = 0;
        for (size_t i = 0; i <= currentLine.length(); ++i) {
            float x_i = x_base + MeasureText(currentLine.substr(0, i).c_str(), textBoxTextSize);
            if (mouseX < x_i || i == currentLine.length()) {
                pos = i;
                break;
            }
        }

        // Calculate m_cursorPos
        size_t startIndex = getLineStartIndex(actualLine, lines);
        m_cursorPos = startIndex + pos;
        if (m_cursorPos > m_content.size()) m_cursorPos = m_content.size(); // Ensure m_cursorPos is within bounds
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_isHovering) {
        m_isTyping = false;
    }

    // Handle mouse wheel for scrolling
    if (m_isHovering) {
        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            auto lines = splitIntoLines(m_content);
            int maxLines = static_cast<int>((m_box.height - 10) / textBoxTextSize);
            if (maxLines < 1) maxLines = 1;
            if (wheel > 0 && m_firstVisibleLine > 0) {
                m_firstVisibleLine--;
            }
            else if (wheel < 0 && m_firstVisibleLine < lines.size() - maxLines) {
                m_firstVisibleLine++;
            }
        }
    }

    // Handle typing
    if (m_isTyping) {
        auto lines = splitIntoLines(m_content);
        size_t charIndex = 0;
        size_t cursorLine = 0;
        size_t cursorPosInLine = 0;
        for (size_t i = 0; i < lines.size(); ++i) {
            if (m_cursorPos <= charIndex + lines[i].length()) {
                cursorLine = i;
                cursorPosInLine = m_cursorPos - charIndex;
                break;
            }
            charIndex += lines[i].length() + 1;
        }
        if (m_cursorPos > charIndex) {
            cursorLine = lines.size() - 1;
            cursorPosInLine = lines.back().length();
        }

        // Handle character input
        int input = GetCharPressed();
        while (input > 0) {
            if (m_content.length() < m_maxLength) {
                if (isalpha(input) || isdigit(input) || input == ' ' || input == '-') {
                    m_content.insert(m_cursorPos, 1, (char)input);
                    m_cursorPos++;
                }
            }
            input = GetCharPressed();
        }

        // Handle backspace
        if (IsKeyPressed(KEY_BACKSPACE) && m_cursorPos > 0) {
            m_content.erase(m_cursorPos - 1, 1);
            m_cursorPos--;
        }

        // Handle delete
        if (IsKeyPressed(KEY_DELETE) && m_cursorPos < m_content.size()) {
            m_content.erase(m_cursorPos, 1);
        }

        // Handle left arrow
        if (IsKeyPressed(KEY_LEFT) && m_cursorPos > 0) {
            m_cursorPos--;
        }

        // Handle right arrow
        if (IsKeyPressed(KEY_RIGHT) && m_cursorPos < m_content.size()) {
            m_cursorPos++;
        }

        // Handle up arrow
        if (IsKeyPressed(KEY_UP) && cursorLine > 0) {
            size_t prevLine = cursorLine - 1;
            size_t newPosInLine = std::min(cursorPosInLine, lines[prevLine].length());
            size_t startIndex = getLineStartIndex(prevLine, lines);
            m_cursorPos = startIndex + newPosInLine;
        }

        // Handle down arrow
        if (IsKeyPressed(KEY_DOWN) && cursorLine < lines.size() - 1) {
            size_t nextLine = cursorLine + 1;
            size_t newPosInLine = std::min(cursorPosInLine, lines[nextLine].length());
            size_t startIndex = getLineStartIndex(nextLine, lines);
            m_cursorPos = startIndex + newPosInLine;
        }

        // Handle enter
        if (IsKeyPressed(KEY_ENTER)) {
            m_content.insert(m_cursorPos, 1, '\n');
            m_cursorPos++;
        }

        // Adjust m_firstVisibleLine to keep cursor visible
        int maxLines = static_cast<int>((m_box.height - 10) / textBoxTextSize);
        if (maxLines < 1) maxLines = 1;
        if (cursorLine < m_firstVisibleLine) {
            m_firstVisibleLine = cursorLine;
        }
        else if (cursorLine >= m_firstVisibleLine + maxLines) {
            m_firstVisibleLine = cursorLine - maxLines + 1;
        }
    }

}

void ShPTextBox::render() {
    // Draw the textbox
    DrawRectangleRec(m_box, m_boxColor);
    DrawRectangleLinesEx(m_box, 2, BLACK);

    // Split m_content into lines
    auto lines = splitIntoLines(m_content);

    // Calculate maxLines
    int maxLines = static_cast<int>((m_box.height - 10) / textBoxTextSize);
    if (maxLines < 1) maxLines = 1;

    // Draw visible lines
    float y = m_box.y + 5;
    for (size_t i = m_firstVisibleLine; i < m_firstVisibleLine + maxLines && i < lines.size(); ++i) {
        DrawText(lines[i].c_str(), m_box.x + 7, y + (i - m_firstVisibleLine) * textBoxTextSize, textBoxTextSize, m_textColor);
    }

    // Draw blinker if typing and cursor is visible
    if(m_isTyping && m_showBlinker) {
        if (lines.empty()) {
            // Draw blinker at the beginning
            float x_blinker = m_box.x + 7;
            float y_blinker = m_box.y + 5;
            DrawText("|", x_blinker, y_blinker, textBoxTextSize, m_textColor);
        }
        else {
            // Existing code to calculate cursorLine and cursorPosInLine
            size_t charIndex = 0;
            size_t cursorLine = 0;
            size_t cursorPosInLine = 0;
            for (size_t i = 0; i < lines.size(); ++i) {
                if (m_cursorPos <= charIndex + lines[i].length()) {
                    cursorLine = i;
                    cursorPosInLine = m_cursorPos - charIndex;
                    break;
                }
                charIndex += lines[i].length() + 1;
            }
            if (m_cursorPos > charIndex) {
                cursorLine = lines.size() - 1;
                cursorPosInLine = lines.back().length();
            }

            if (cursorLine >= m_firstVisibleLine && cursorLine < m_firstVisibleLine + maxLines) {
                float x_blinker = m_box.x + 7 + MeasureText(lines[cursorLine].substr(0, cursorPosInLine).c_str(), textBoxTextSize);
                float y_blinker = y + (cursorLine - m_firstVisibleLine) * textBoxTextSize;
                DrawText("|", x_blinker, y_blinker, textBoxTextSize, m_textColor);
            }
        }
    }
}

void ShPTextBox::setText(std::string content) {
    m_content = content;
    m_cursorPos = 0;
    m_firstVisibleLine = 0;
}

std::string ShPTextBox::getText() {
    return m_content;
}

void ShPTextBox::clearContent() {
    m_content.clear();
    m_cursorPos = 0;
    m_firstVisibleLine = 0;
}

void ShPTextBox::setPosition(Vector2 position) {
    m_box.x = position.x;
    m_box.y = position.y;
}

void ShPTextBox::setBoxSize(Vector2 size) {
    m_box.width = size.x;
    m_box.height = size.y;
}

std::vector<std::string> ShPTextBox::splitIntoLines(const std::string& content) {
    std::vector<std::string> lines;
    std::stringstream ss(content);
    std::string line;
    while (std::getline(ss, line, '\n')) {
        lines.push_back(line);
    }
    if (lines.empty()) {
        lines.push_back(""); // Ensure there's at least one line
    }
    return lines;
}

size_t ShPTextBox::getLineStartIndex(size_t lineNumber, const std::vector<std::string>& lines) {
    size_t startIndex = 0;
    for (size_t k = 0; k < lineNumber; ++k) {
        startIndex += lines[k].length() + 1; // +1 for '\n'
    }
    return startIndex;
}