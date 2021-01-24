#include "Ground.h"

Ground::Ground(float x, float y, float width, float height):Actor(x,y, 0," ",0) 
{
	m_collisionBox.x = x;
	m_collisionBox.y = y;
	m_collisionBox.width = width;
	m_collisionBox.height = height;
}

Ground::Ground(float x, float y, float width, float height, const char* spriteFilePath) : Actor(x, y, 0,spriteFilePath, 0)
{
	m_collisionBox.x = x;
	m_collisionBox.y = y;
	m_collisionBox.width = width;
	m_collisionBox.height = height;
}

bool Ground::checkCollision(Actor* other)
{
	Vector2 center;
	center.x = other->getWorldPosition().x;
	center.y = other->getWorldPosition().y;
	
	return CheckCollisionCircleRec(center,other->getCollisionRadius(),m_collisionBox);
}     

void Ground::onCollision(Actor* other)
{
	other->setAcceleration(MathLibrary::Vector2(0, -1));
}

void Ground::draw()
{
	DrawRectangleLines(m_collisionBox.x*32,m_collisionBox.y*32,m_collisionBox.width*32,m_collisionBox.height*32, WHITE);
	Actor::draw();
}
