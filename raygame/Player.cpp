#include "Player.h"


Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Entity(x, y, collisionRadius, spriteFilePath, maxSpeed, health, damage)
{
	strncpy_s(tag,"Player",16);
}

void Player::onCollision(Actor* other)
{
	attack((Entity*)other);
	if (getTag() == "ground")
	{
		setAcceleration(MathLibrary::Vector2(0, -1));
	}
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);
	if (IsKeyPressed(KeyboardKey::KEY_SPACE))
	{
		setAcceleration(MathLibrary::Vector2(0,-5));
	}  
	setVelocity(MathLibrary::Vector2(xdirection,0) + m_gravity);
	Actor::update(deltaTime);
}
