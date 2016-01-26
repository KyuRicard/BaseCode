#pragma once
#include "EntityParams.h"

class Entity
{
public:
	EntityParams * params;
	void(*callback)(Entity *, Entity *);

	virtual void Load(EntityParams * params) = 0;
	virtual void Draw() = 0;
	virtual void DrawFrame() = 0;
	virtual void Update() = 0;
	virtual void Clear() = 0;

	void setOnCollide(void(*cbk)(Entity * base, Entity * second))
	{
		this->callback = cbk;
	}
	void onCollide(Entity * other)
	{
		if (callback != nullptr)
		{
			callback(this, other);
		}
	}
	
	int gid;
	std::string texture;
};

