#include "Entity.h"
class Ground : public Entity
{
	Ground() : Entity() {};
	Ground(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage);
	~Ground();
};
