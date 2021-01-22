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
	if (strcmp(other->getTag(), "Ground") == 0)
	{
		setAcceleration(MathLibrary::Vector2(0, -50));
	}
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);
	
	Entity::update(deltaTime);

	setAcceleration(m_gravity);

	if (IsKeyPressed(KeyboardKey::KEY_SPACE))
	{
		setAcceleration(MathLibrary::Vector2(0, -10));
	}

	setVelocity(MathLibrary::Vector2(xdirection, 0) * m_maxSpeed);
	if (xdirection > 0)//direction manipulation
	{
		setForward(MathLibrary::Vector2(1, 0));
	}
	else
		setForward(MathLibrary::Vector2(-1, 0));
}

void Player::draw()
{ 
	Entity::draw();
}
