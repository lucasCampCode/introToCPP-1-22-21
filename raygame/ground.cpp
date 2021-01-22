#include "Ground.h"

Ground::Ground(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	:Entity(x, y, collisionRadius, spriteFilePath, maxSpeed, health, damage)
{
	strncpy_s(tag, "Ground", 16);
}
Ground::~Ground()
{
	Entity::~Entity();
}

bool Ground::checkCollision(Actor* other)
{
	Vector2 center;
	center.x = other->getWorldPosition().x;
	center.y = other->getWorldPosition().y;
	return CheckCollisionCircleRec(center,other->collisionRadius,m_CollisionBox);
}

void Ground::onCollision(Actor* other)
{
	if (strcmp(other->tag,"Actor") == 0) 
	{
		
	}
}

void Ground::setCollidingbox(float width,float hieght)
{
	m_CollisionBox.x = getWorldPosition().x;
	m_CollisionBox.y = getWorldPosition().y;
	m_CollisionBox.width = width;
	m_CollisionBox.height = hieght;
}
