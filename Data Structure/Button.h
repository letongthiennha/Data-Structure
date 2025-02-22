#include "raylib.h"
#include "GUIObject.h"
#include<string>
class Button : public GUIObject {
private:
    Rectangle hitBox;
    float width, height;
    std::string text;

    Color idleColor=BLACK;
    Color hoverColor=YELLOW;
    Color activeColor=RED;

    Color renderColor = idleColor;
    Vector2 textPos;
    int textSize=30;
    void ComputeTextPos();
    float activeTimer;      
    const float clickDuration = 0.17f;
public:
    // Constructor
    Button() = default;
    Button(float x, float y, float width, float height, std::string text);
    // Destructor
    virtual ~Button() = default;
    //Set Color
    void SetIdleColor(Color color);
    void SetHoverColor(Color color);
    void SetActiveColor(Color color);
    //Set Text
    void SetTextSize(int textSize);
    void SetTextPos(Vector2 TextPos);
    // Render
    void update();
    void render() override;
    bool isHover() const;
    bool isClicked() const;
};
