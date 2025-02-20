#include "raylib.h"
#include "GUIObject.h"
#include<string>
class Button : public GUIObject {
protected:
    Rectangle rect;
    std::string text;

    Color idleColor=BLACK;
    Color hoverColor=YELLOW;
    Color activeColor=RED;
public:
    // Constructor
    Button() = default;
    Button(float x, float y, float width, float height, std::string text);
    // Destructor
    virtual ~Button() = default;
    // Render
    void render() override;
    bool isHover() const;
    bool isClicked() const;

};