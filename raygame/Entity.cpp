#include "Entity.h"
#include "Game.h"
#include "raylib.h"

Entity::Entity(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	m_health = health;
	m_damage = damage;
}

bool Entity::attack(Entity* other)
{
	other->takeDamage(m_damage);
	return true;
}

bool Entity::takeDamage(float totalDamage)
{
	m_health -= totalDamage;
	return true;
}


void Entity::onCollision(Actor* other)
{
	attack((Entity*)other);
}

void Entity::update(float deltaTime)
{
	Actor::update(deltaTime);
}

void Entity::draw()
{
}
