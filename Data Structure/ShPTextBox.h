#include "raylib.h"
#include <string>
#include <vector>

class ShPTextBox {
public:
    ShPTextBox(Vector2 position, Vector2 size, Color boxColor, Color textColor, int maxLength);
    void update();
    void render();
    void setText(std::string content);
    std::string getText();
    void clearContent();
    void setPosition(Vector2 position);
    void setBoxSize(Vector2 size);

private:
    Rectangle m_box;            // Position and size of the textbox
    Color m_boxColor;           // Background color
    Color m_textColor;          // Text color
    std::string m_content;      // Text content
    int m_maxLength;            // Maximum allowed characters
    bool m_isTyping;            // Whether the textbox is active for typing
    bool m_showBlinker;         // Blinking cursor visibility
    float m_timer;              // Timer for blinker
    bool m_isHovering;          // Whether mouse is hovering over textbox
    size_t m_cursorPos;         // Cursor position in the content
    size_t m_firstVisibleLine;  // First visible line for scrolling

    // Constants for styling (adjust as needed)
    static const Color textBoxColor;         // Idle color
    static const Color textBoxColorInputing; // Active color
    static const int textBoxTextSize;        // Text size

    // Helper functions
    std::vector<std::string> splitIntoLines(const std::string& content);
    size_t getLineStartIndex(size_t lineNumber, const std::vector<std::string>& lines);
};