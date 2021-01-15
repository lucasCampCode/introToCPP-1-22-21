#include "Player.h"

void Player::onCollision(Actor* other)
{
	attack((Entity*)other);
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);


	Actor::update(deltaTime);
}
