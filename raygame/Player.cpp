#include "Player.h"

Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Entity(x, y, collisionRadius, spriteFilePath, maxSpeed, health, damage)
{
}

void Player::onCollision(Actor* other)
{
	attack((Entity*)other);
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);

	setVelocity(MathLibrary::Vector2(xdirection, 0));
	Actor::update(deltaTime);
}
