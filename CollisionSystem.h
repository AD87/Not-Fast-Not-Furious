#pragma once
#include "GameObject.h"

class CollisionSystem{
public:
	virtual ~CollisionSystem(){}
	virtual void checkCollisions(GameObjectMap*) = 0;

	virtual void addGameObject(int id, GameObject* go){}
	virtual void deleteGameObject(int id){}
};