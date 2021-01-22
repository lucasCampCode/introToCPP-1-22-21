#include "Ground.h"

Ground::Ground(float x, float y, float width, float height, const char* spriteFilePath)
	:Actor(x, y, 0, spriteFilePath, 0)
{
	m_CollisionBox.x = x;
	m_CollisionBox.y = y;
	m_CollisionBox.width = width;
	m_CollisionBox.height = height;
	setTag("Ground");
}
Ground::~Ground()
{
	Actor::~Actor();
}

bool Ground::checkCollision(Actor* other)
{
	Vector2 center;
	center.x = other->getWorldPosition().x;
	center.y = other->getWorldPosition().y;
	bool result = CheckCollisionCircleRec(center, other->getCollisionRadius(), m_CollisionBox);
	return result;
}

void Ground::onCollision(Actor* other)
{
	if (strcmp(other->getTag(),"Actor") != 0)
	{
		other->setAcceleration(MathLibrary::Vector2(0, -1));
	}
}

void Ground::draw()
{
	DrawRectangleLinesEx(m_CollisionBox,5,WHITE);
}

void Ground::setCollidingbox(float width,float hieght)
{
	m_CollisionBox.width = width;
	m_CollisionBox.height = hieght;
}
