#include "Player.h"

Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Entity(x, y, collisionRadius, spriteFilePath, maxSpeed, health, damage)
{
	setTag("Player");
}

Player::~Player()
{
	Entity::~Entity();
}


void Player::onCollision(Actor* other)
{
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);
	int ydirection = IsKeyDown(KeyboardKey::KEY_S) - IsKeyDown(KeyboardKey::KEY_W);

	setVelocity(MathLibrary::Vector2(xdirection, ydirection) * m_maxSpeed);
	Entity::update(deltaTime);
}

void Player::draw()
{ 
	Entity::draw();
}
