#include "button.h"
#include "Game.h"

Button::Button(float x, float y, float width, float height, Color color, const char* text, int fontSize) 
	: Actor(x, y, 0, " ", 0)
{
	m_box.x = x;
	m_box.y = y;
	m_box.width = width;
	m_box.height = height;
	m_fontSize = fontSize;
	m_color = color;
	m_text = text;
}

void Button::update(float deltaTime)
{
	//if mouse is over the box and clicks set current scene to sceneindex
	if (CheckCollisionPointRec(GetMousePosition(), m_box) && IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON)) 
	{
		buttonClicked = true;
	}
}

void Button::draw()
{
	DrawRectangleRec(m_box, m_color);
	DrawText(m_text, m_box.x + offsetTextX, m_box.y + offSetTextY, m_fontSize, RAYWHITE);
}
