#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
public:
    Enemy() : Entity() {};
    Enemy(float x, float y, float collisionRadius,const char* spriteFilePath,float maxSpeed,float health, float damage);
public:
    bool checkTargetInSight(float maxAngle, float maxDistance);
    void setTarget(Actor* other) { m_target = other; }
    void onCollision(Actor* other) override;
    void update(float deltaTime) override;
    
private:
    Actor* m_target;
};

