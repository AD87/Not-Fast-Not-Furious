#pragma once
#include "CollisionSystem.h"

//simple collision system = brute force
class SimpleCollisionSystem : public CollisionSystem{
public:
	virtual void checkCollisions(GameObjectMap* gos)override;

};