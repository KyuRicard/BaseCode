#include "Camera.h"
#include "Tools.h"
#include <cmath>

using namespace std;

Camera * Camera::instancia = 0;

void Camera::SetTarget(Player * player)
{
	this->target = player;
}

void Camera::SetPosition(const Vector2D * position)
{
	posicio = *position;
}

void Camera::SetMaxPosition(int maxPos)
{
	this->maxPosition = maxPos;
}

const Vector2D * Camera::GetPosition()
{
	if (target != NULL)
	{
		Vector2D * position = new Vector2D();
		position->X = target->position.X - (Tools::GetWidth() / 2);
		position->Y = 0;
		position->X = (float)fmax(position->X, 0);
		position->X = (float)fmin(position->X, maxPosition - Tools::GetWidth());
		return position;
	}
	else 
	{
		return Vector2D::NULL_VECTOR;
	}
}