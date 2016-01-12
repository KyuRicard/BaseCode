#include "Player.h"
#include "Game.h"
#include <string>
#include <sdl.h>

Player::~Player()
{
}

Player::Player() : LivingEntity()
{
	position.X = 0;
	maxVel = Vector2D(10, 100);
	acceleration = Vector2D(1, 1);
	if (TheGame->DEBUG)
		friction = Vector2D(0, 0);
}

void Player::Update()
{
	Accelerate(xAccel, yAccel);	
	LivingEntity::Update();	
}

bool Player::InBounds(LivingEntity * entitat)
{
	return Tools::InBounding(entitat, this);
}

void Player::Jump()
{
 	if (this->GetYPos() + this->GetHeight() == Tools::GetHeight())
	{
		velocity.Y = salt;
	}
}
