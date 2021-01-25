#pragma once
#include "Entity.h"
#include "raylib.h"
class Player : public Entity
{
public:
	Player() :Entity() {};
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float health, float damage);
	~Player();
public: 
	void onCollision(Actor* other) override;
	void start() override;
	void update(float deltaTime) override;
	void draw() override;
	void end() override;
	float* m_spriteTimerPointer = &m_spriteTimer;
private:
	int m_currentSprite = 0;
	float m_spriteTimer;
	bool m_spriteTimerStarted;
	void m_setTimerGoing(bool value);
	int incrementSprite();
};

