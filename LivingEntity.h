#pragma once
#include "Entity.h"
#include "Vector2D.h"
#include "Layer.h"
#include "TileLayer.h"

#define NEGATIVE -1
#define POSITIVE 1
#define NULL 0

class LivingEntity :
	public Entity
{
public:
	Vector2D position, velocity, maxVel, acceleration, friction;	

	LivingEntity();
	~LivingEntity();

	int xAccel = 0, yAccel = 0;
	bool inAir = false;
	int collisionMargin;

	static LivingEntity * Create() { return new LivingEntity(); }
	void Move(float, float);

	void Accelerate(int, int);
	virtual void Die();

	virtual void Load(EntityParams *);
	virtual void Draw();
	virtual void DrawFrame();
	virtual void Update();
	static void CheckCollisions(LivingEntity * ent, std::vector<Entity *> entitats) {
		for each (LivingEntity * entity in entitats)
		{
			bool collide = ent->CollideWithAnotherEntity(entity);
			if (collide)
			{
				ent->onCollide(entity);
			}
		}
	}
	void Clear();

	std::string GetId() { return params->GetId(); }
	float GetXPos() { return position.X; }
	float GetYPos() { return position.Y; }
	void SetYPos(float yPos) { this->position.Y = yPos; }
	int GetWidth() { return params->GetWidth(); }
	int GetHeight() { return params->GetHeight(); }
	
	bool HaveAnimation() { return params->GetMaxFrame() > 1; }
	int GetFrame() { return params->GetFrame(); }
	int GetRow() { return params->GetRow(); }

	bool IsCollidingWithTile(int, int);
	void LoadCollisionLayers(std::vector<TileLayer *> *);
	
	bool CollideWithAnotherEntity(LivingEntity *);
	
private:
	std::vector<TileLayer *> * collisionLayers;	
	int getYGravity(int x, int y);
};