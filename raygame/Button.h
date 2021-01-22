#pragma once
#include "Actor.h"
#include "raylib.h"
class Button :
    public Actor
{
public:
    Button() : Actor() {};
    Button(float x, float y, float width, float height, Color color, const char* text, int fontSize);
    Button(float x, float y, float width, float height,  Color color, const char* text,int fontSize, int sceneIndex);
    void update(float deltaTime) override;
    void draw() override;
private:
    int m_sceneIndex;
    int m_fontSize;
    Rectangle m_box;
    Color m_color;
    const char* m_text;
};

