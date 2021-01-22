#include "Entity.h"
#include "raylib.h"
class Ground : public Actor
{
public:
	Ground() : Actor() {};
	Ground(float x, float y, const char* spriteFilePath, float width, float height);
	~Ground();
	bool checkCollision(Actor* other) override;
	void onCollision(Actor* other) override;
	void setCollidingbox(float width,float height);
private:
	Rectangle m_CollisionBox;
};
