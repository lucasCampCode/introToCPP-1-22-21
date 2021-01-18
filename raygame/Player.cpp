#include "Player.h"


Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Entity(x, y, collisionRadius, spriteFilePath, maxSpeed, health, damage)
{
	strncpy_s(tag,"Player",16);
}

Player::~Player()
{
	Entity::~Entity();
}


void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);
	if (IsKeyPressed(KeyboardKey::KEY_SPACE))
	{
		setAcceleration(MathLibrary::Vector2(0,-50));
	}
	if (xdirection > 0)
	{
		setForward(MathLibrary::Vector2(1,0));
	}
	else
		setForward(MathLibrary::Vector2(-1, 0));
	setAcceleration(getAcceleration() + m_gravity);
	setVelocity(MathLibrary::Vector2(xdirection,0) * m_maxSpeed);
	Actor::update(deltaTime);
}

void Player::draw()
{ 
	Entity::draw();
}
