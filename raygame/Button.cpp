#include "button.h"
#include "Game.h"

Button::Button(float x, float y, float width, float height, Color color, const char* text, int fontSize)
{
	m_box.x = x;
	m_box.y = y;
	m_box.width = width;
	m_box.height = height;
	m_fontSize = fontSize;
	m_sceneIndex = -1;
	m_color = color;
	m_text = text;
}

Button::Button(float x, float y, float width, float height, Color color, const char* text,int fontSize, int sceneIndex) : Actor(x, y, 0, " ", 0)
{
	m_box.x = x;
	m_box.y = y;
	m_box.width = width;
	m_box.height = height;
	m_fontSize = fontSize;
	m_sceneIndex = sceneIndex;
	m_color = color;
	m_text = text;
}

void Button::update(float deltaTime)
{
	//if mouse is over the box and clicks set current scene to sceneindex
	if (CheckCollisionPointRec(GetMousePosition(), m_box) && IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON) && m_sceneIndex >= 0) 
	{
		Game::setCurrentScene(m_sceneIndex);
	}
	else if (CheckCollisionPointRec(GetMousePosition(), m_box) && IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON) && m_sceneIndex < 0) 
	{

	}
}

void Button::draw()
{
	DrawRectangleRec(m_box, m_color);
	DrawText(m_text, m_box.x - MeasureText(m_text,m_fontSize), m_box.y, m_fontSize, RAYWHITE);
}
