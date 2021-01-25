#include "Wall.h"

Wall::Wall(float x, float y, float width, float height) : Actor(x, y, 0, " ", 0)
{
	m_collisionBox.x = x - width / 2;
	m_collisionBox.y = y - height / 2;
	m_collisionBox.width = width;
	m_collisionBox.height = height;
}

bool Wall::checkCollision(Actor* other)
{
	Vector2 point;
	point.x = other->getWorldPosition().x;
	point.y = other->getWorldPosition().y + other->getCollisionRadius();

	return CheckCollisionPointRec(point,m_collisionBox);
}

void Wall::onCollision(Actor* other)
{
	if (other->getWorldPosition().x < m_collisionBox.width && other->getWorldPosition().x >m_collisionBox.width - 2 && other->getWorldPosition().y > m_collisionBox.y && other->getWorldPosition().y < m_collisionBox.height)
		other->setVelocity(MathLibrary::Vector2(1,0));
	if (other->getWorldPosition().x > m_collisionBox.x && other->getWorldPosition().x < m_collisionBox.x + 2 && other->getWorldPosition().y > m_collisionBox.y && other->getWorldPosition().y < m_collisionBox.height)
		other->setVelocity(MathLibrary::Vector2(-1, 0));
	if (other->getWorldPosition().x > m_collisionBox.x && other->getWorldPosition().x < m_collisionBox.width && other->getWorldPosition().y < m_collisionBox.height && other->getWorldPosition().y > m_collisionBox.height-2)
		other->setVelocity(MathLibrary::Vector2(0, 1));
	if (other->getWorldPosition().x > m_collisionBox.x && other->getWorldPosition().x < m_collisionBox.width && other->getWorldPosition().y > m_collisionBox.y && other->getWorldPosition().y < m_collisionBox.y + 2)
		other->setVelocity(MathLibrary::Vector2(0, -1));

}
void Wall::draw() 
{
	DrawRectangleLines(m_collisionBox.x*32,m_collisionBox.y*32,m_collisionBox.width*32,m_collisionBox.height*32 , WHITE);
}
