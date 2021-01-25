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

void Player::start()
{
	Entity::start();
	m_setTimerGoing(true);
}

void Player::update(float deltaTime)
{
	int xdirection = IsKeyDown(KeyboardKey::KEY_D) - IsKeyDown(KeyboardKey::KEY_A);
	int ydirection = IsKeyDown(KeyboardKey::KEY_S) - IsKeyDown(KeyboardKey::KEY_W);
	if (m_spriteTimerStarted == true && ((*m_spriteTimerPointer += deltaTime) >= .15))
	{
		if (xdirection > 0)
			changeSprite(sprites[1][incrementSprite()]);
		else if (xdirection < 0)
			changeSprite(sprites[2][incrementSprite()]);
		*m_spriteTimerPointer = 0;
	}	

	setVelocity(MathLibrary::Vector2(xdirection, ydirection) * m_maxSpeed);
	Entity::update(deltaTime);
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

int Player::incrementSprite()
{
	m_currentSprite++;
	if (m_currentSprite > 2) { m_currentSprite = 0; }
	return m_currentSprite;
}
