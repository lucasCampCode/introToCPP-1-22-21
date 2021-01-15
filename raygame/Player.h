#pragma once
#include "Entity.h"
#include "raylib.h"
class Player : public Entity
{
public:
	void onCollision(Actor* other) override;
	void update(float deltaTime) override;
};

