#pragma once
#include "Actor.h"
class Entity : public Actor
{
public:
	Entity() : Actor() {};
	Entity(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage);
private:
	
public:
	virtual bool attack(Entity* other);
	virtual bool takeDamage(float totalDamage);

	void onCollision(Actor* other) override;
	void update(float deltaTime) override;
	void draw() override;
private:
	bool m_isColliding = false;
	float m_health;
	float m_damage;
};

