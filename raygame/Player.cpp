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
	if (typeid(*other) == typeid(Entity)) {
		DrawText("hi there",300,50,20,WHITE);
	}
}

void Player::start()
{
	Entity::start();
	m_setTimerGoing(true);
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);
	if (m_spriteTimerStarted == true && ((m_spriteTimer += deltaTime) >= 5))
	{
		changeSprite(sprites[m_currentSprite + 1]);
	}	

	Entity::update(deltaTime);

	setAcceleration(getAcceleration() + m_gravity);

	if (IsKeyPressed(KeyboardKey::KEY_SPACE))
	{
		setAcceleration(MathLibrary::Vector2(0, -50));
	}

	setVelocity(MathLibrary::Vector2(xdirection, 0) * m_maxSpeed);
}

void Player::draw()
{ 
	Entity::draw();
}

void Player::end()
{
	Entity::end();
	m_setTimerGoing(false);
}

void Player::m_setTimerGoing(bool value)
{
	m_spriteTimerStarted = value;
}