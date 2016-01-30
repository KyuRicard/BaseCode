#pragma once
#include "Game.h"
#include "LivingEntity.h"

class Metaflag : LivingEntity
{
public:
	Metaflag()
	{
		setOnCollide(([](Entity * mf, Entity * other) {
			if (Player * pl = dynamic_cast<Player *>(other))
			{
				TheGame->LevelUp();
				((LivingEntity *)mf)->Die();
			}
		}));
	}

	static Entity * Create()
	{
		return new Metaflag();
	}
};