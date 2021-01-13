#pragma once
#include "Actor.h"
class Entity : public Actor
{
public:
	Entity() : Actor() {};
	Entity(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed);
private:
	
public:
	bool attack(Entity other);
	virtual bool takeDamage(float totalDamage);
private:
	bool m_isColliding = false;
	float m_health;
	float m_damage;
};

