#pragma once
#include "Actor.h"
#include "raylib.h"
class Ground :
    public Actor
{
public: 
    Ground() : Actor() {};
    Ground(float x, float y, float width, float height);
    Ground(float x, float y, float width, float height, const char* spriteFilePath);
    virtual bool checkCollision(Actor* other) override;
    virtual void onCollision(Actor* other) override;
    virtual void draw() override;
private:
    Rectangle m_collisionBox;
};

