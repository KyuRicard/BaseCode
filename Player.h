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
	int invulnerable = 0;
	int lives = 3;
	void Load(EntityParams *);
	void Update();
	void Jump();
	void Damage();
	bool InBounds(LivingEntity *);
	void DrawFrame();
	void onVoid();
	void unStuck();
	void SetJump(float jump)
	{
		salt = jump;
	}
	static Entity * Create() { return new Player(); }
};