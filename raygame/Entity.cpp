#include "Entity.h"
#include "Game.h"
#include "raylib.h"

Entity::Entity(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
	m_health = health;
	m_damage = damage;
	strncpy(m_tag, "Entity", 16);
}
/// <summary>
/// this instance of the entity attacks the other instance
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
bool Entity::attack(Entity* other)
{
	other->takeDamage(m_damage);
	return true;
}
/// <summary>
/// this instance takes damages
/// </summary>
/// <param name="totalDamage"></param>
/// <returns></returns>
bool Entity::takeDamage(float totalDamage)
{
	m_health -= totalDamage;
	return true;
}

void Entity::onCollision(Actor* other)
{

}

void Entity::update(float deltaTime)
{
	Actor::update(deltaTime);
}

void Entity::draw()
{
}
