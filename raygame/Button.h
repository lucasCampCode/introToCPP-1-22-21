#pragma once
#include "Actor.h"
#include "raylib.h"
class Button :
    public Actor
{
public:
    Button() : Actor() {};
    Button(float x, float y, float width, float height, Color color, const char* text, int fontSize);
    bool getButtonClicked() { return buttonClicked; }
    void offsetText(MathLibrary::Vector2 value) { offsetTextX = value.x; offSetTextY = value.y; }
    void update(float deltaTime) override;
    void draw() override;
private:
    bool buttonClicked;
    int m_fontSize;
    int offsetTextX;
    int offSetTextY;
    Rectangle m_box;
    Color m_color;
    const char* m_text;
};

