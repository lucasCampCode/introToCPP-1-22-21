#pragma once
#include "Actor.h"
class Entity : public Actor
{
public:
	Entity() : Actor() {};
	Entity(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed) {};
private:
	
public:
	bool attack(Actor other);
	virtual bool takeDamage(float totalDamage);
private:
	float m_health;
	float m_damage;
	bool m_isColliding;
};

