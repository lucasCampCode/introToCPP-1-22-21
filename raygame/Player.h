#pragma once
#include "Entity.h"
#include "raylib.h"
class Player : public Entity
{
public:
	Player() :Entity() {};
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage);
public:
	void onCollision(Actor* other) override;
	void update(float deltaTime) override;
};

