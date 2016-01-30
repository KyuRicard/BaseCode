#include "CollisionManager.h"

CollisionManager * CollisionManager::instance = 0;

bool CollisionManager::isColliding(LivingEntity * self, LivingEntity * another)
{
	if (self == NULL || another == NULL || self->GetId() == another->GetId()) {
		return false;
	}

	Vector2D aMin = Vector2D(self->position.X + self->collisionMargin, self->position.Y);
	Vector2D aMax = Vector2D(self->position.X + self->GetWidth() - self->collisionMargin, self->position.Y + self->GetHeight());
	Vector2D bMin = Vector2D(another->position.X + another->collisionMargin, another->position.Y);
	Vector2D bMax = Vector2D(another->position.X + another->GetWidth() - another->collisionMargin, another->position.Y + another->GetHeight());

	return (aMin.X < bMax.X) && (aMax.X > bMin.X) && (aMin.Y < bMax.Y) && (aMax.Y > bMin.Y);
}

void CollisionManager::CheckCollisions(LivingEntity * self, vector<Entity *> entitats) {
	for each (LivingEntity * entity in entitats)
	{
		bool collide = isColliding(self, entity);
		if (collide)
		{
			self->onCollide(entity);
		}
	}
}