#include "Ground.h"

Ground::Ground(float x, float y, const char* spriteFilePath, float width, float height)
	:Actor(x, y, 0, spriteFilePath, 0)
{
	m_CollisionBox.x = x;
	m_CollisionBox.y = y;
	m_CollisionBox.width = width;
	m_CollisionBox.height = height;
	setTag("ground");
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
	return CheckCollisionCircleRec(center,other->getCollisionRadius(),m_CollisionBox);
}

void Ground::onCollision(Actor* other)
{
	if (other->getTag() != "Actor") 
	{
		setAcceleration(MathLibrary::Vector2(0, 0));
	}
}

void Ground::setCollidingbox(float width,float hieght)
{
	m_CollisionBox.width = width;
	m_CollisionBox.height = hieght;
}
