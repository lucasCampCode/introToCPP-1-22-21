#pragma once
#include "Actor.h"
#include "raylib.h"
class Wall : public Actor
{
public:
	Wall() : Actor() {};
	Wall(float x, float y, float width, float height);
	Rectangle getWall() { return m_collisionBox; }
	bool checkCollision(Actor* other) override;
	void onCollision(Actor* other)override;
	void draw() override;
private:
	Rectangle m_collisionBox;
};

