#pragma once
#include "LivingEntity.h"
#include "Player.h"
#include <time.h>
#include "Vector2D.h"

#define STATIC_ENEMY 0
#define FOLLOWER_ENEMY 1
#define IGNORE_ENEMY 2
#define LITTLE_MOVEMENT 3

class Enemy :
	public LivingEntity
{
private:
	int type = 0;
	void FollowPlayer(Player *);
	void BeStatic(Player *);
	void TheIgnored();
	void MoveALittle();
	Vector2D playerPos;
public:
	Enemy(int);
	~Enemy();
	void Update(Player *);
	static Entity * Create() { return new Enemy(STATIC_ENEMY); }
	void SetType(int type) { this->type = type; }
};
