#include "Enemy.h"
#include <SDL.h>
#include "Game.h"

void Enemy::FollowPlayer(Player * player)
{
	float xPos = position.X;
	float playerXPos = player->GetXPos();
	float delta = (float)Game::GetInstance()->delta;

	if (abs(xPos - playerXPos) < 1) {
		xAccel = NULL;
		xPos = playerXPos;
	} else if (xPos > playerXPos) {
		xAccel = NEGATIVE;
	} else if (xPos < playerXPos) {
		xAccel = POSITIVE;
	}	
}

void Enemy::BeStatic(Player * player)
{
	float xPos = position.X;
	float playerXPos = player->GetXPos();
	
	if (xPos > playerXPos && !params->IsFlipped()) {
		params->Flip();
	}
	else if (xPos < playerXPos && params->IsFlipped()) {
		params->Flip();
	}		
	
}

void Enemy::MoveALittle()
{	
	srand((int)time(NULL));
	int random = rand() % 10;
	if (random > 2 && random < 8)
	{
		xAccel = NULL;
	}
	else if (random <= 2)
	{
		xAccel = NEGATIVE;
	}
	else if (random >= 8)
	{
		xAccel = POSITIVE;
	}
}

Enemy::Enemy(int type)
{
	this->type = type;
	maxVel = Vector2D(7.5, 10);
	acceleration = Vector2D(0.75, 1);	
}


Enemy::~Enemy()
{
}

void Enemy::Update(Player * player)
{
	if (invulnerable > 0)
		invulnerable--;
	playerPos = player->position;	
	Accelerate(xAccel, yAccel);	
}

void Enemy::SetType(int type)
{
	this->type = type;
	switch (type)
	{
	case IGNORE_ENEMY:
		setOnCollide(([](Entity * base, Entity * second)
		{
			if (second == NULL) {
				Enemy * enemy = dynamic_cast<Enemy *>(base);
				if (enemy->invulnerable > 0)
					return;
				enemy->params->Flip();
				if (enemy->params->IsFlipped())
				{
					enemy->xAccel = NEGATIVE;
				}
				else {
					enemy->xAccel = POSITIVE;
				}
				enemy->invulnerable = 30;
			}			
		}));
		xAccel = NEGATIVE;
	}
}