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
		if (target->position.Y > Tools::GetHeight()) {
			cout << 2 << endl;
		}
		position->X = target->position.X - (Tools::GetWidth() / 2);
		position->Y = target->position.Y - (Tools::GetHeight() / 3);
		position->X = (float)fmax(position->X, 0);
		position->X = (float)fmin(position->X, maxPosition - Tools::GetWidth());
		position->Y = (float)fmin(position->Y, 0);
		return position;
	}
	else 
	{
		return Vector2D::NULL_VECTOR;
	}
}