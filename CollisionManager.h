#pragma once
#include <vector>
#include "LivingEntity.h"

#define CheckCollision CollisionManager::getInstance()->CheckCollisions

class CollisionManager
{
private:
	CollisionManager() {
		//Not interesting...
	};
	static CollisionManager * instance;
	bool isColliding(LivingEntity *, LivingEntity *);
public:	
	~CollisionManager() {
		//This neither
		instance = NULL;
	}
	static CollisionManager * getInstance() {
		if (instance == NULL) {
			instance = new CollisionManager();
		}
		return instance;
	}
	void CheckCollisions(LivingEntity *, vector<Entity *>);
};

