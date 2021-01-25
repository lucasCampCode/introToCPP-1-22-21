#include "Enemy.h"
#include "Player.h"
Enemy::Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage)
	: Entity(x,y,collisionRadius,spriteFilePath,maxSpeed,health,damage)
{

}

bool Enemy::checkTargetInSight(float maxAngle, float maxDistance)
{
	if (m_target == NULL)
		return false;
	MathLibrary::Vector2 direction = m_target->getWorldPosition() - getWorldPosition();

	float distance = direction.getMagnitude();
	float angle = (float)_CMATH_::acos(MathLibrary::Vector2::dotProduct(getVelocity(), direction));

	if (angle < maxAngle && distance <= maxDistance)
		return true;

	return false;
}

void Enemy::onCollision(Actor* other)
{
	if(typeid(*other) == typeid(Player))
		attack((Entity*)other);
	other->setVelocity(getVelocity());
}

void Enemy::update(float deltaTime)
{
	if (checkTargetInSight(1, 3)) 
	{

	}
	else
	{

	}

}
