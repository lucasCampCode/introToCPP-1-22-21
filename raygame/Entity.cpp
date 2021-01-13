#include "Entity.h"

Entity::Entity(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	
}

bool Entity::attack(Entity other)
{
	other.takeDamage(m_damage);
	return true;
}

bool Entity::takeDamage(float totalDamage)
{
	m_health -= totalDamage;
	return true;
}