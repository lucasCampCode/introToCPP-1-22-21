#include "Entity.h"
#include "raylib.h"
class Ground : public Entity
{
public:
	Ground() : Entity() {};
	Ground(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage);
	~Ground();
	bool checkCollision(Actor* other) override;
	void onCollision(Actor* other) override;
	void setCollidingbox(float width,float hieght);
private:
	Rectangle m_CollisionBox;
};
