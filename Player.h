#pragma once
#include "LivingEntity.h"
#include <SDL.h>
#include <vector>

class Player : public LivingEntity
{
private:
	float salt;
public:
	Player();
	~Player();	
	void Update();
	void Jump();
	bool InBounds(LivingEntity *);
	void SetJump(float jump)
	{
		salt = jump;
	}
	static Entity * Create() { return new Player(); }
};