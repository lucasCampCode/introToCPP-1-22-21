#include "Player.h"
#include "Ground.h"

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
	if (typeid(*other) == typeid(Ground))
	{

	}
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);
	

	setAcceleration(getAcceleration() + m_gravity);

	if (IsKeyPressed(KeyboardKey::KEY_SPACE))
	{
		setAcceleration(MathLibrary::Vector2(0, -50));
	}

	setVelocity(MathLibrary::Vector2(xdirection, 0) * m_maxSpeed);
	Entity::update(deltaTime);
}

void Player::draw()
{ 
	Entity::draw();
}
