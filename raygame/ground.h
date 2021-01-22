#include "Entity.h"
#include "raylib.h"
class Ground : public Actor
{
public:
	Ground() : Actor() {};
	Ground(float x, float y, float width, float height, const char* spriteFilePath);
	~Ground();
	bool checkCollision(Actor* other) override;
	void onCollision(Actor* other) override;
	void draw() override;
	void setCollidingbox(float width,float height);

private:
	Rectangle m_CollisionBox;
};
